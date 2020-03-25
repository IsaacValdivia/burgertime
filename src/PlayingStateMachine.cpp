#include "PlayingStateMachine.hpp"
#include "InputSystem.hpp"
#include "Enemy.hpp"
#include <iostream>

FSM_INITIAL_STATE(PlayingStateMachine, EnterStatePlaying)

BurgerTimeController &PlayingStateMachine::controller = BurgerTimeController::get();
GUI &PlayingStateMachine::gui = GUI::get();

void PlayingStateMachine::addPepper(const sf::Vector2f &launchPosition, Direction direction)
{
    deletePepper();
    pepper = std::make_shared<Pepper>(launchPosition, direction, std::bind(&PlayingStateMachine::deletePepper, this));
    controller.addDrawable(pepper);
}

void PlayingStateMachine::deletePepper()
{
    pepper = nullptr;
}

void EnterStatePlaying::entry()
{
    // TODO: change
    currentScore = 0;
    controller.clearScreen();

    auto oneUpText = gui.createText("playingStateOneUp", "1UP", sf::Vector2u(150, 20), sf::Vector2f(0.5, 0.5), sf::Color::Red);

    auto hiScoreText = gui.createText("playingStateHiScore", "HI-SCORE", sf::Vector2u(300, 20), sf::Vector2f(0.5, 0.5), sf::Color::Red);
    
    pepperText = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*pepperText, BT_sprites::Sprite::PEPPER);
    pepperText->setPosition(78 * WINDOW_WIDTH / 100, 16 * WINDOW_HEIGHT / 1000);
    pepperText->setScale(2, 2);

    // currentScoreText = std::make_shared<sf::Text>();
    // currentScoreText->setFont(controller.font);
    // currentScoreText->setString(std::to_string(currentScore));
    // currentScoreText->setFillColor(sf::Color::White);
    // currentScoreText->setScale(0.5, 0.5);
    // currentScoreText->setPosition( * WINDOW_WIDTH / 100 , 2 * WINDOW_HEIGHT / 100);

    map = std::make_shared<Map>("maps/map1.map");
    ingmap = std::make_shared<IngredientMap>("maps/map1.ingmap");
    player = std::make_shared<Player>(map->data[0][17].shape.getPosition(), map, std::bind(&PlayingStateMachine::addPepper, this, std::placeholders::_1, std::placeholders::_2));

    static auto ia = IA(map, map->data[0][17]);

    player->connect_player_moved(std::bind(&IA::setGoalTile, &ia, std::placeholders::_1));

    auto egg = std::make_shared<Enemy>(map->data[0][10].shape.getPosition(), Enemy::sausage_sprite_state_machine, map, ia);
    enemies.push_back(egg);

    controller.addDrawable(map);
    controller.addDrawable(ingmap);
    controller.addDrawable(egg);
    controller.addDrawable(player);
    controller.addDrawable(pepperText);
    controller.addDrawable(oneUpText);
    controller.addDrawable(hiScoreText);
    // controller.addDrawable(currentScoreText);
}

void EnterStatePlaying::react(const ExecuteEvent &event)
{
    for (const auto &enemy : enemies)
    {
        if (player->getCollisionShape().intersects(enemy->getCollisionShape())) {
            // TODO: tachan
            // std::cout << "intersects" << std::endl;
        }
    }

    if (pepper)
    {
        for (const auto &enemy : enemies)
        {
            if (pepper->getCollisionShape().intersects(enemy->getCollisionShape())) {
                // TODO: algo?
                enemy->pepper();
            }
        }
    }

    player->update(event.deltaT);
    for (const auto &enemy : enemies)
    {
        enemy->update(event.deltaT);
    }
    if (pepper)
    {
        pepper->update(event.deltaT);
    }
}
