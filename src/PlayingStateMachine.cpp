#include "PlayingStateMachine.hpp"
#include "InputSystem.hpp"

FSM_INITIAL_STATE(PlayingStateMachine, EnterStatePlaying)

BurgerTimeController &PlayingStateMachine::controller = BurgerTimeController::get();
GUI &PlayingStateMachine::gui = GUI::get();

void PlayingStateMachine::addPepper(sf::Vector2f launchPosition, Direction direction)
{
    deletePepper();
    pepper = std::make_shared<Pepper>(launchPosition, direction, *this);
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
    player = std::make_shared<Player>(map->data[0][4].shape.getPosition(), map, *this);

    controller.addDrawable(map);
    controller.addDrawable(player);
    controller.addDrawable(pepperText);
    controller.addDrawable(oneUpText);
    controller.addDrawable(hiScoreText);
    // controller.addDrawable(currentScoreText);
}

void EnterStatePlaying::react(const ExecuteEvent &event)
{
    player->update(event.deltaT);
    if (pepper)
    {
        pepper->update(event.deltaT);
    }
    // player->win();
    // transit<StartOptionState>();
}
