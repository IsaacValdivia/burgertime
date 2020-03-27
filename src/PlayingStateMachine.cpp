#include "PlayingStateMachine.hpp"
#include "InputSystem.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <filesystem>

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

    std::vector<fs::path> paths;
    for (const auto &mapFile : fs::directory_iterator(MAPS_FOLDER))
    {
        if (mapFile.is_regular_file())
        {
            paths.push_back(mapFile.path());
        }
    }
    //std::greater<string>();
    std::sort(paths.begin(), paths.end());

    for (const auto &mapPath : paths)
    { 
        if (mapPath.extension().string() == MAP_EXTENSION)
        {
            gameInfo->maps.push_back(std::make_shared<Map>(mapPath.string()));
        }
        else if (mapPath.extension().string() == INGMAP_EXTENSION)
        {
            gameInfo->ingMaps.push_back(std::make_shared<IngredientMap>(mapPath.string()));
        }
    }

    auto &map = gameInfo->maps[gameInfo->currentMap];
    auto &ingMap = gameInfo->ingMaps[gameInfo->currentMap];

    const auto &playerSpawnTile = map->data[ingMap->chef_spawn.x][ingMap->chef_spawn.y];

    sf::Vector2f initPos = playerSpawnTile.shape.getPosition();
    initPos.y -= Map::Y_PADDING;
    gameInfo->player = std::make_shared<Player>(initPos, map, std::bind(&PlayingStateMachine::addPepper, this, std::placeholders::_1, std::placeholders::_2));

    static auto ia = AI(map, playerSpawnTile);

    // TODO: cambiar
    float offset = 1;
    for (const auto &enemySpawn : ingMap->enemy_spawns)
    {
        // gameInfo->ias.emplace_back(map, map->data[0][17]);

        // ias.push_back(ia);
        gameInfo->player->connect_player_moved(std::bind(&AI::setGoalTile, &ia, std::placeholders::_1));
        // gameInfo->player->connect_player_moved(std::bind(&AI::setGoalTile, &gameInfo->ias.back(), std::placeholders::_1));
        const Enemy::Sprite_state_machine *enemySprites;
        switch (enemySpawn.first)
        {
            case IngredientMap::SAUSAGE:
                enemySprites = Enemy::sausage_sprite_state_machine;
                break;
            case IngredientMap::PICKLE:
                enemySprites = Enemy::pickle_sprite_state_machine;
                break;
            case IngredientMap::EGG:
                enemySprites = Enemy::egg_sprite_state_machine;
                break;
        }

        auto initialPos = map->data[enemySpawn.second.x][enemySpawn.second.y].shape.getPosition();
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
    controller.addDrawable(ingMap);
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

    for (const auto &ingredient : gameInfo->ingMaps[gameInfo->currentMap]->data)
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

    for (auto &ingredient : gameInfo->ingMaps[gameInfo->currentMap]->data)
    {
        ingredient.update(event.deltaT);
    }

    if (gameInfo->pepper)
    {
        gameInfo->pepper->update(event.deltaT);
    }
}