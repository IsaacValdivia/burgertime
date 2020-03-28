#include "PlayingStateMachine.hpp"
#include "InputSystem.hpp"
#include "Enemy.hpp"
#include "BurgerTimeStateMachine.hpp"
#include <iostream>
#include <filesystem>
#include <set>

namespace fs = std::filesystem;

FSM_INITIAL_STATE(PlayingStateMachine, EnterStatePlaying)

BurgerTimeController &PlayingStateMachine::controller = BurgerTimeController::get();
GUI &PlayingStateMachine::gui = GUI::get();

void PlayingStateMachine::addPepper(const sf::Vector2f &launchPosition, Direction direction)
{
    if (current_state_ptr->gameInfo->currentPepper > 0)
    {
        current_state_ptr->gameInfo->currentPepper--;
        current_state_ptr->deletePepper();
        current_state_ptr->gameInfo->pepper = std::make_shared<Pepper>(launchPosition, direction, std::bind(&PlayingStateMachine::deletePepper, this));
        gui.getText("playingStatePepper").lock()->setString(GUI::fixTextToRight(std::to_string(current_state_ptr->gameInfo->currentPepper), 3));
        controller.addDrawable(current_state_ptr->gameInfo->pepper);
    }
    else
    {
        // TODO: exception
    }   
}

bool PlayingStateMachine::hasPepper() const
{
    return current_state_ptr->gameInfo->currentPepper > 0;
}

void PlayingStateMachine::addPlayerAndEnemies()
{
    gameInfo->enemies.clear();
    auto &map = gameInfo->maps[gameInfo->currentMap];

    const auto &playerSpawnTile = map->tile_data[map->chef_spawn.x][map->chef_spawn.y];

    sf::Vector2f initPos = playerSpawnTile->shape.getPosition();
    initPos.y -= playerSpawnTile->height;
    gameInfo->player = std::make_shared<Player>(initPos, map, 
        std::bind(&PlayingStateMachine::addPepper, this, std::placeholders::_1, std::placeholders::_2), 
        std::bind(&PlayingStateMachine::hasPepper, this)
    );

    gameInfo->ai = std::make_shared<AI>(map, playerSpawnTile);

    // TODO: cambiar
    float offset = 1;
    for (const auto &enemySpawn : map->enemy_spawns)
    {
        // gameInfo->ias.emplace_back(map, map->data[0][17]);

        // ias.push_back(ia);
        gameInfo->player->connect_player_moved(std::bind(&AI::setGoalTile, gameInfo->ai, std::placeholders::_1));
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

        const auto &initialTile = map->tile_data[enemySpawn.second.x][enemySpawn.second.y];
        auto initialPos = initialTile->shape.getPosition();
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
        initialPos.y -= initialTile->height;

        // sf::Vector2

        offset += 1.2;

        gameInfo->enemies.push_back(std::make_shared<Enemy>(initialPos, enemySprites, map, *gameInfo->ai, initialDir));
        // gameInfo->enemies.push_back(std::make_shared<Enemy>(initialPos, enemySprites, map, gameInfo->ias.back(), initialDir));
    }
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
    controller.clearScreen();
    gameInfo = std::unique_ptr<GameInfo>(new GameInfo);

    gameInfo->currentMap = 0;
    gameInfo->currentScore = 0;
    gameInfo->currentIngredients = 0;
    gameInfo->currentLives = 3;
    gameInfo->currentPepper = 5;
    controller.clearScreen();

    gameInfo->curtains[0] = std::make_shared<sf::RectangleShape>();
    gameInfo->curtains[0]->setFillColor(sf::Color::Black);
    gameInfo->curtains[0]->setPosition(sf::Vector2f(0, 0));
    gameInfo->curtains[0]->setSize(sf::Vector2f(2 * Tile::TILE_WIDTH, WINDOW_HEIGHT));
    gameInfo->curtains[1] = std::make_shared<sf::RectangleShape>();
    gameInfo->curtains[1]->setFillColor(sf::Color::Black);
    gameInfo->curtains[1]->setPosition(sf::Vector2f(WINDOW_WIDTH - 2 * Tile::TILE_WIDTH, 0));
    gameInfo->curtains[1]->setSize(sf::Vector2f(2 * Tile::TILE_WIDTH, WINDOW_HEIGHT));

    gui.createText("playingStateOneUp", "1UP", sf::Vector2u(150, 20), sf::Vector2f(0.5, 0.5), sf::Color::Red);
    gui.createText("playingStateHiScore", "HI-SCORE", sf::Vector2u(300, 20), sf::Vector2f(0.5, 0.5), sf::Color::Red);
    gui.createText("playingStatePepper", GUI::fixTextToRight(std::to_string(gameInfo->currentPepper), 3), sf::Vector2u(763, 48), sf::Vector2f(0.5, 0.5), sf::Color::White);

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
}

void EnterStatePlaying::react(const ExecuteEvent &event)
{
    transit<GameReadyScreenState>(std::bind(&EnterStatePlaying::changeGameInfo, this));
}


void GameReadyScreenState::entry()
{
    controller.clearScreen();

    auto text = gui.createText("gameReadyText", "GAME READY", sf::Vector2u(250, 500), sf::Vector2f(0.8, 0.8));
    addPlayerAndEnemies();

    controller.addDrawable(text);
    controller.restartTimer();
}

void GameReadyScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact(1))
    {
        // TODO: change
        transit<NormalStatePlaying>(std::bind(&GameReadyScreenState::changeGameInfo, this));
        // transit<EnterHighscoreState>(std::bind(&EnterHighscoreState::setHighScore, 999999));
    }
}


void NormalStatePlaying::entry()
{
    controller.clearScreen();

    controller.addDrawable(gameInfo->maps[gameInfo->currentMap]);
    for (const auto &enemy : gameInfo->enemies)
    {
        controller.addDrawable(enemy);
    }
    controller.addDrawable(gameInfo->player);
    controller.addDrawable(gameInfo->pepperText);
    controller.addDrawable(gui.getText("playingStateOneUp"));
    controller.addDrawable(gui.getText("playingStateHiScore"));
    controller.addDrawable(gui.getText("playingStatePepper"));
    controller.addDrawable(gameInfo->curtains[0]);
    controller.addDrawable(gameInfo->curtains[1]);
    // controller.addDrawable(currentScoreText);
}

void NormalStatePlaying::react(const ExecuteEvent &event)
{
    auto &map = gameInfo->maps[gameInfo->currentMap];
    for (const auto &enemy : gameInfo->enemies)
    {
        if (!enemy->isPeppered() && gameInfo->player->intersectsWith(*enemy)) {
#if true
            if (gameInfo->currentLives > 0)
            {
                transit<DeadStatePlaying>(std::bind(&NormalStatePlaying::changeGameInfo, this));
                return;
            }
#endif
        }
    }

    for (auto &ingredient : map->ing_data)
    {
        if (gameInfo->player->goingXdirection())
        {
            ingredient.stepped(gameInfo->player->getCollisionShape());
        }

        if (ingredient.isFalling())
        {
            const auto tiles = map->entityOnTiles(ingredient);
            if (tiles.size() > 1)
            {
                if (tiles[1]->isSteppableHor())
                {
                    for (auto &other : map->ing_data)
                    {
                        if (&other != &ingredient) 
                        {
                            if (other.intersectsWith(ingredient))
                            {
                                other.land(tiles[1]->shape.getPosition().y + 10);
                                other.drop();
                                break;
                            }
                        }
                    }

                    ingredient.land(tiles[1]->shape.getPosition().y + (Tile::TILE_HEIGHT - 8));
                }
                else if (tiles[1]->isBasket() || tiles[1]->isBasketEdge())
                {
                    gameInfo->currentIngredients++;
                    ingredient.land(tiles[1]->shape.getPosition().y + (Tile::TILE_HEIGHT - 12));
                }
            }
        }
    }

    if (gameInfo->currentIngredients == map->ing_data.size())
    {
        transit<WinStatePlaying>(std::bind(&NormalStatePlaying::changeGameInfo, this));
        return;
    }

    if (gameInfo->pepper)
    {
        for (const auto &enemy : gameInfo->enemies)
        {
            if (gameInfo->pepper->intersectsWith(*enemy)) {
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

    for (auto &ingredient : map->ing_data)
    {
        ingredient.update(event.deltaT);
    }

    if (gameInfo->pepper)
    {
        gameInfo->pepper->update(event.deltaT);
    }
}


void DeadStatePlaying::entry()
{
    controller.restartTimer();
    gameInfo->currentLives--;
    gameInfo->player->die();
}

void DeadStatePlaying::react(const ExecuteEvent &event)
{
    if (BurgerTimeStateMachine::timedStateReact(4))
    {
        if (gameInfo->currentLives == 0)
        {
            transit<GameOverStatePlaying>();
        }
        else
        {
            transit<GameReadyScreenState>(std::bind(&DeadStatePlaying::changeGameInfo, this));
        }
        
        // TODO: change
        // transit<EnterHighscoreState>(std::bind(&EnterHighscoreState::setHighScore, 999999));
    }
    else
    {
        auto &map = gameInfo->maps[gameInfo->currentMap];
        gameInfo->player->update(event.deltaT);

        for (auto &ingredient : map->ing_data)
        {
            ingredient.update(event.deltaT);
        }
    }
}


void WinStatePlaying::entry()
{
    controller.restartTimer();
    gameInfo->player->win();
    gameInfo->currentMap = (gameInfo->currentMap + 1) % gameInfo->maps.size();
    gameInfo->currentIngredients = 0;
}

void WinStatePlaying::react(const ExecuteEvent &event)
{
    if (BurgerTimeStateMachine::timedStateReact(4))
    {
        // TODO: change
        transit<GameReadyScreenState>(std::bind(&WinStatePlaying::changeGameInfo, this));
        // transit<EnterHighscoreState>(std::bind(&EnterHighscoreState::setHighScore, 999999));
    }
    else
    {
        gameInfo->player->update(event.deltaT);
    }
}


void GameOverStatePlaying::entry()
{
    gameInfo = nullptr;
}