#include "PlayingStateMachine.hpp"
#include "InputSystem.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <filesystem>
#include <set>

namespace fs = std::filesystem;

FSM_INITIAL_STATE(PlayingStateMachine, EnterStatePlaying)

BurgerTimeController &PlayingStateMachine::controller = BurgerTimeController::get();
GUI &PlayingStateMachine::gui = GUI::get();

void PlayingStateMachine::addPepper(const sf::Vector2f &launchPosition, Direction direction)
{
    current_state_ptr->deletePepper();
    current_state_ptr->gameInfo->pepper = std::make_shared<Pepper>(launchPosition, direction, std::bind(&PlayingStateMachine::deletePepper, this));
    controller.addDrawable(current_state_ptr->gameInfo->pepper);
}

void PlayingStateMachine::deletePepper()
{
    current_state_ptr->gameInfo->pepper = nullptr;
}

void PlayingStateMachine::changeGameInfo()
{
    current_state_ptr->setGameInfo(std::move(gameInfo));
}

void PlayingStateMachine::setGameInfo(std::unique_ptr<GameInfo> newGameInfo)
{
    gameInfo = std::move(newGameInfo);
}


void EnterStatePlaying::entry()
{
    gameInfo = std::unique_ptr<GameInfo>(new GameInfo);

    // TODO: change
    gameInfo->currentMap = 5;
    gameInfo->currentScore = 0;
    controller.clearScreen();

    gameInfo->curtains[0] = std::make_shared<sf::RectangleShape>();
    gameInfo->curtains[0]->setFillColor(sf::Color::Black);
    gameInfo->curtains[0]->setPosition(sf::Vector2f(0, 0));
    gameInfo->curtains[0]->setSize(sf::Vector2f(2 * Tile::TILE_WIDTH, WINDOW_HEIGHT));
    gameInfo->curtains[1] = std::make_shared<sf::RectangleShape>();
    gameInfo->curtains[1]->setFillColor(sf::Color::Black);
    gameInfo->curtains[1]->setPosition(sf::Vector2f(WINDOW_WIDTH - 2 * Tile::TILE_WIDTH, 0));
    gameInfo->curtains[1]->setSize(sf::Vector2f(2 * Tile::TILE_WIDTH, WINDOW_HEIGHT));

    auto oneUpText = gui.createText("playingStateOneUp", "1UP", sf::Vector2u(150, 20), sf::Vector2f(0.5, 0.5), sf::Color::Red);

    auto hiScoreText = gui.createText("playingStateHiScore", "HI-SCORE", sf::Vector2u(300, 20), sf::Vector2f(0.5, 0.5), sf::Color::Red);

    gameInfo->pepperText = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*gameInfo->pepperText, BT_sprites::Sprite::PEPPER);
    gameInfo->pepperText->setPosition(78 * WINDOW_WIDTH / 100, 16 * WINDOW_HEIGHT / 1000);
    gameInfo->pepperText->setScale(2, 2);

    // currentScoreText = std::make_shared<sf::Text>();
    // currentScoreText->setFont(controller.font);
    // currentScoreText->setString(std::to_string(currentScore));
    // currentScoreText->setFillColor(sf::Color::White);
    // currentScoreText->setScale(0.5, 0.5);
    // currentScoreText->setPosition( * WINDOW_WIDTH / 100 , 2 * WINDOW_HEIGHT / 100);

    std::set<std::string> mapStems;
    for (const auto &mapFile : fs::directory_iterator(MAPS_FOLDER))
    {
        if (mapFile.is_regular_file())
        {
            mapStems.insert(MAPS_FOLDER + std::string("/") + mapFile.path().stem().string());
        }
    }
    std::vector<std::string> mapNames(mapStems.begin(), mapStems.end());
    std::sort(mapNames.begin(), mapNames.end());

    for (const auto &mapName : mapNames)
    { 
        gameInfo->maps.push_back(std::make_shared<Map>(mapName));
    }

    auto &map = gameInfo->maps[gameInfo->currentMap];

    const auto &playerSpawnTile = map->tile_data[map->chef_spawn.x][map->chef_spawn.y];

    sf::Vector2f initPos = playerSpawnTile->shape.getPosition();
    initPos.y -= Map::Y_PADDING;
    gameInfo->player = std::make_shared<Player>(initPos, map, std::bind(&PlayingStateMachine::addPepper, this, std::placeholders::_1, std::placeholders::_2));

    static auto ia = AI(map, playerSpawnTile);

    // TODO: cambiar
    float offset = 1;
    for (const auto &enemySpawn : map->enemy_spawns)
    {
        // gameInfo->ias.emplace_back(map, map->data[0][17]);

        // ias.push_back(ia);
        gameInfo->player->connect_player_moved(std::bind(&AI::setGoalTile, &ia, std::placeholders::_1));
        // gameInfo->player->connect_player_moved(std::bind(&AI::setGoalTile, &gameInfo->ias.back(), std::placeholders::_1));
        const Enemy::Sprite_state_machine *enemySprites;
        switch (enemySpawn.first)
        {
            case Map::SAUSAGE:
                enemySprites = Enemy::sausage_sprite_state_machine;
                break;
            case Map::PICKLE:
                enemySprites = Enemy::pickle_sprite_state_machine;
                break;
            case Map::EGG:
                enemySprites = Enemy::egg_sprite_state_machine;
                break;
        }

        auto initialPos = map->tile_data[enemySpawn.second.x][enemySpawn.second.y]->shape.getPosition();
        Direction initialDir;
        if (abs(gameInfo->curtains[0]->getPosition().x - initialPos.x) < abs(gameInfo->curtains[1]->getPosition().x - initialPos.x))
        {
            initialDir = Direction::RIGHT;
            initialPos.x -= offset * 5 * Tile::TILE_WIDTH;
        }
        else
        {
            initialDir = Direction::LEFT;
            initialPos.x += offset * 5 * Tile::TILE_WIDTH;
        }
        initialPos.y -= Map::Y_PADDING;

        // sf::Vector2

        offset += 1.2;

        gameInfo->enemies.push_back(std::make_shared<Enemy>(initialPos, enemySprites, map, ia, initialDir));
        // gameInfo->enemies.push_back(std::make_shared<Enemy>(initialPos, enemySprites, map, gameInfo->ias.back(), initialDir));
    }

    controller.addDrawable(map);
    for (const auto &enemy : gameInfo->enemies)
    {
        controller.addDrawable(enemy);
    }
    controller.addDrawable(gameInfo->player);
    controller.addDrawable(gameInfo->pepperText);
    controller.addDrawable(oneUpText);
    controller.addDrawable(hiScoreText);
    controller.addDrawable(gameInfo->curtains[0]);
    controller.addDrawable(gameInfo->curtains[1]);
    // controller.addDrawable(currentScoreText);
}

void EnterStatePlaying::react(const ExecuteEvent &event)
{
    transit<NormalStatePlaying>();
    changeGameInfo();
}

void NormalStatePlaying::react(const ExecuteEvent &event)
{
    for (const auto &enemy : gameInfo->enemies)
    {
        if (gameInfo->player->getCollisionShape().intersects(enemy->getCollisionShape())) {
            // TODO: tachan
            // std::cout << "intersects" << std::endl;
        }
    }

    for (auto &ingredient : gameInfo->maps[gameInfo->currentMap]->ing_data)
    {
        ingredient.stepped(gameInfo->player->getCollisionShape());
    }

    if (gameInfo->pepper)
    {
        for (const auto &enemy : gameInfo->enemies)
        {
            if (gameInfo->pepper->getCollisionShape().intersects(enemy->getCollisionShape())) {
                // TODO: algo?
                enemy->pepper();
            }
        }
    }

    gameInfo->player->update(event.deltaT);

    for (const auto &enemy : gameInfo->enemies)
    {
        enemy->update(event.deltaT);
    }

    for (auto &ingredient : gameInfo->maps[gameInfo->currentMap]->ing_data)
    {
        ingredient.update(event.deltaT);
    }

    if (gameInfo->pepper)
    {
        gameInfo->pepper->update(event.deltaT);
    }
}