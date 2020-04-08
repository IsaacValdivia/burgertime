#include "PlayingStateMachine.hpp"
#include "InputSystem.hpp"
#include "Enemy.hpp"
#include "BurgerTimeStateMachine.hpp"
#include "Audio.hpp"
#include "HighScores.hpp"
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <set>
#include <random>

namespace fs = std::filesystem;

void PlayingStateMachine::PepperCounter::changePepper(int change)
{
    if (currentPepper + change >= 0)
    {
        currentPepper += change;
        gui.getText("playingStatePepper").lock()->setString(GUI::fixTextToRight(std::to_string(currentPepper), 3));
    }
}

bool PlayingStateMachine::PepperCounter::hasPepper() const
{
    return currentPepper != 0;
}

PlayingStateMachine::PepperCounter::PepperCounter() : currentPepper(5)
{
    gui.createText("playingStatePepper", GUI::fixTextToRight(std::to_string(currentPepper), 3), sf::Vector2u(763, 48), sf::Vector2f(0.5, 0.5), sf::Color::White);
}


void PlayingStateMachine::LivesCounter::changeLives(int change)
{
    currentLives += change;
    gui.getText("playingStateLives").lock()->setString(GUI::fixTextToRight(std::to_string(currentLives), 3));
}

bool PlayingStateMachine::LivesCounter::hasLives() const
{
    return currentLives != 0;
}

PlayingStateMachine::LivesCounter::LivesCounter() : currentLives(3)
{
    gui.createText("playingStateLives", GUI::fixTextToRight(std::to_string(currentLives), 3), sf::Vector2u(1, 860), sf::Vector2f(0.5, 0.5), sf::Color::White);
}


void PlayingStateMachine::ScoreCounter::addPoints(uint32_t points)
{
    currentScore += points;

    if (currentScore > currentTopScore)
    {
        currentTopScore = currentScore;
        gui.getText("playingStateTopScore").lock()->setString(GUI::fixTextToRight(std::to_string(currentScore), MAX_SCORE_CHARS));
    }

    gui.getText("playingStateScore").lock()->setString(GUI::fixTextToRight(std::to_string(currentScore), MAX_SCORE_CHARS));
}

uint32_t PlayingStateMachine::ScoreCounter::getScore() const
{
    return currentScore;
}


PlayingStateMachine::ScoreCounter::ScoreCounter() : currentScore(0), currentTopScore(HighScores().getTopScore())
{
    gui.createText("playingStateScore", GUI::fixTextToRight(std::to_string(currentScore), MAX_SCORE_CHARS), sf::Vector2u(50, 48), sf::Vector2f(0.5, 0.5), sf::Color::White);
    gui.createText("playingStateTopScore", GUI::fixTextToRight(std::to_string(currentTopScore), MAX_SCORE_CHARS), sf::Vector2u(300, 48), sf::Vector2f(0.5, 0.5), sf::Color::White);
}


void PlayingStateMachine::LevelCounter::addLevel(uint32_t level)
{
    currentLevel += level;
    gui.getText("playingStateLevel").lock()->setString(GUI::fixTextToRight(std::to_string(currentLevel), 3));
}

PlayingStateMachine::LevelCounter::LevelCounter() : currentLevel(1)
{
    gui.createText("playingStateLevel", GUI::fixTextToRight(std::to_string(currentLevel), 3), sf::Vector2u(800, 860), sf::Vector2f(0.5, 0.5), sf::Color::White);
}


FSM_INITIAL_STATE(PlayingStateMachine, EnterStatePlaying)

BurgerTimeController &PlayingStateMachine::controller = BurgerTimeController::get();
GUI &PlayingStateMachine::gui = GUI::get();

void PlayingStateMachine::addPepper(const sf::Vector2f &launchPosition, Direction direction)
{
    if (current_state_ptr->gameInfo->pepperCounter.hasPepper())
    {
        Audio::play(Audio::Track::PEPPER);

        current_state_ptr->gameInfo->pepperCounter.changePepper(-1);
        current_state_ptr->deletePepper();
        current_state_ptr->gameInfo->pepper = std::make_shared<Pepper>(launchPosition, direction, std::bind(&PlayingStateMachine::deletePepper, this));
        controller.addDrawable(current_state_ptr->gameInfo->pepper);
    }
    else
    {
        // TODO: exception
    }
}

bool PlayingStateMachine::hasPepper() const
{
    return current_state_ptr->gameInfo->pepperCounter.hasPepper();
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

    float offset = 1;
    for (const auto &enemySpawn : map->enemy_spawns)
    {
        const auto &initialTile = map->tile_data[enemySpawn.second.x][enemySpawn.second.y];
        spawnEnemy(static_cast<Enemy::Type>(enemySpawn.first), *initialTile, offset);
        offset += 1.2;
    }
}

void PlayingStateMachine::spawnEnemy(const Enemy::Type &type, const Tile &initialTile, float offset)
{
    auto &map = gameInfo->maps[gameInfo->currentMap];
    // TODO: ia
    gameInfo->player->connect_player_moved(std::bind(&AI::setGoalTile, gameInfo->ai, std::placeholders::_1));
    // gameInfo->player->connect_player_moved(std::bind(&AI::setGoalTile, &gameInfo->ias.back(), std::placeholders::_1));

    auto initialPos = initialTile.shape.getPosition();
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
    initialPos.y -= initialTile.height;

    // sf::Vector2
    const Enemy::Sprite_state_machine *enemySprites;

    switch (type)	
    {	
        case Enemy::Type::SAUSAGE:	
            enemySprites = Enemy::sausage_sprite_state_machine;	
            break;	
        case Enemy::Type::PICKLE:	
            enemySprites = Enemy::pickle_sprite_state_machine;	
            break;	
        case Enemy::Type::EGG:	
            enemySprites = Enemy::egg_sprite_state_machine;	
            break;	
    }	

    gameInfo->enemies.push_back(std::make_shared<Enemy>(type, initialPos, enemySprites, map, *gameInfo->ai, initialDir, std::bind(&PlayingStateMachine::addPoints, this, std::placeholders::_1)));
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

void PlayingStateMachine::ingredientCollision()
{
    auto &map = gameInfo->maps[gameInfo->currentMap];
    for (auto &ingredient : map->ing_data)
    {
        int enemiesSurfing = 0;

        if (ingredient.isFalling())
        {
            const auto tiles = map->entityOnTiles(ingredient);
            if (tiles.size() > 1)
            {
                if (tiles[1]->isSteppableHor())
                {
                    ingredient.land(tiles[1]->shape.getPosition().y + (Tile::TILE_HEIGHT - 8), Ingredient::FLOOR);
                }
                else if (tiles[1]->isBasket() || tiles[1]->isBasketEdge())
                {
                    ingredient.land(tiles[1]->shape.getPosition().y + (Tile::TILE_HEIGHT - 12), Ingredient::STATIC_ING_BASKET);
                }
            }

            for (auto &other : map->ing_data)
            {
                if (&other != &ingredient)
                {
                    if (other.intersectsWith(ingredient) && (other.isIdle() || other.isStatic()))
                    {
                        addPoints(50);
                        auto state = other.isStatic() ? Ingredient::STATIC_ING_BASKET : Ingredient::INGREDIENT;
                        // other.land(tiles[1]->shape.getPosition().y +
                        // 10, Ingredient::INGREDIENT);
                        // std::cout << "other state " << other.state << std::endl;
                        ingredient.land(other.getCollisionShape().top - (Tile::TILE_HEIGHT - 8), state);
                        other.drop();
                        break;
                    }
                }
            }

            for (auto &enemy : gameInfo->enemies)
            {
                if (ingredient.intersectsWith(*enemy) && enemy->is_alive())
                {
                    if (ingredient.getCollisionShape().top < enemy->getCollisionShape().top)
                    {
                        enemy->die();
                    }
                }
            }
        }

        for (auto &enemy : gameInfo->enemies)
        {
            if (ingredient.intersectsWith(*enemy) && ingredient.getCollisionShape().top >= enemy->getCollisionShape().top)
            {
                enemiesSurfing++;
            }
        }

        if (ingredient.testStatic())
        {
            gameInfo->currentIngredients++;
        }

        if (gameInfo->player->goingXdirection())
        {
            if (ingredient.stepped(gameInfo->player->getCollisionShape(), 1 + enemiesSurfing * 2))
            {
                bool firstSurfer = true;
                int surfPoints = std::pow(2, enemiesSurfing - 1) * 500;
                Audio::play(Audio::Track::BURGER_GOING_DOWN);
                addPoints(50);
                for (auto &enemy : gameInfo->enemies)
                {
                    if (!enemy->isSurfing() && ingredient.intersectsWith(*enemy) && ingredient.getCollisionShape().top >= enemy->getCollisionShape().top)
                    {
                        auto connections = ingredient.connect_enemy_surfer(
                            std::bind(&Enemy::move_by_signal, enemy, std::placeholders::_1),
                            std::bind(&Enemy::stop_surfing, enemy));
                        if (firstSurfer)
                        {
                            enemy->start_surfing(std::move(connections.first), std::move(connections.second), surfPoints);
                            firstSurfer = false;
                        }
                        else
                        {
                            enemy->start_surfing(std::move(connections.first), std::move(connections.second), 0);
                        }
                        
                    }
                }
            }
        }
    }
}

void PlayingStateMachine::addPoints(unsigned int points)
{
    current_state_ptr->gameInfo->scoreCounter.addPoints(points);
    current_state_ptr->gameInfo->pointsToExtraLife -= points;

    if (current_state_ptr->gameInfo->pointsToExtraLife <= 0)
    {
        Audio::play(Audio::Track::ONE_UP);
        current_state_ptr->gameInfo->livesCounter.changeLives(1);
        current_state_ptr->gameInfo->pointsToExtraLife = 20000 - current_state_ptr->gameInfo->pointsToExtraLife;
    }
}

uint32_t PlayingStateMachine::getCurrentScore()
{
    return current_state_ptr->gameInfo->scoreCounter.getScore();
}


void EnterStatePlaying::entry()
{
    Audio::play(Audio::Track::LEVEL_INTRO);

    controller.clearScreen();
    gameInfo = std::unique_ptr<GameInfo>(new GameInfo);

    gameInfo->hasJustEntered = true;
    gameInfo->currentMap = 0;
    gameInfo->currentIngredients = 0;
    gameInfo->pointsToExtraLife = 20000;

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

    gameInfo->pepperText = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*gameInfo->pepperText, BT_sprites::Sprite::PEPPER);
    gameInfo->pepperText->setPosition(780 * WINDOW_WIDTH / 1000, 16 * WINDOW_HEIGHT / 1000);
    gameInfo->pepperText->setScale(2, 2);

    gameInfo->livesSprite = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*gameInfo->livesSprite, BT_sprites::Sprite::LIVES);
    gameInfo->livesSprite->setPosition(80 * WINDOW_WIDTH / 1000, 815 * WINDOW_HEIGHT / 1000);
    gameInfo->livesSprite->setScale(2, 2);

    gameInfo->levelSprite = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*gameInfo->levelSprite, BT_sprites::Sprite::MINI_BURGER_1);
    gameInfo->levelSprite->setPosition(880 * WINDOW_WIDTH / 1000, 815 * WINDOW_HEIGHT / 1000);
    gameInfo->levelSprite->setScale(2, 2);


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


void NormalStatePlaying::checkMainMusic()
{
    if (!mainMusicPlayed)
    {
        if (gameInfo->hasJustEntered) {
            auto elapsedTime = controller.getElapsedTime();
            if (elapsedTime.asSeconds() >= 4)
            {
                mainMusicPlayed = true;
                gameInfo->hasJustEntered = false;
                Audio::play(Audio::Track::MAIN);
            }
        } else {
            mainMusicPlayed = true;
            Audio::play(Audio::Track::MAIN);
        }
    }
} 

void NormalStatePlaying::entry()
{
    controller.clearScreen();
    mainMusicPlayed = false;

    auto &map = gameInfo->maps[gameInfo->currentMap];
    for (auto &ingredient : map->ing_data)
    {
        ingredient.resetSteps();
        ingredient.fix_position_up();
    }

    const auto &itemSpawnTile = map->tile_data[map->item_spawn.second.x][map->item_spawn.second.y];

    sf::Vector2f initPos = itemSpawnTile->shape.getPosition();
    // initPos.y -= itemSpawnTile->height;

    BT_sprites::Sprite init_sprite;
    int points;
    switch (map->item_spawn.first)
    {
        case Map::ICE_CREAM:
            init_sprite = BT_sprites::Sprite::ICE_CREAM;
            points = 500;
            break;
        case Map::COFFEE:
            init_sprite = BT_sprites::Sprite::COFFEE;
            points = 1000;
            break;
        case Map::FRIES:
            init_sprite = BT_sprites::Sprite::FRIES;
            points = 1500;
            break;
    }

    gameInfo->bonus = std::make_shared<Bonus>(initPos, init_sprite, points);


    controller.addDrawable(gameInfo->maps[gameInfo->currentMap]);
    controller.addDrawable(gameInfo->bonus);
    for (const auto &enemy : gameInfo->enemies)
    {
        controller.addDrawable(enemy);
    }
    controller.addDrawable(gameInfo->player);
    controller.addDrawable(gameInfo->pepperText);
    controller.addDrawable(gameInfo->livesSprite);
    controller.addDrawable(gameInfo->levelSprite);
    controller.addDrawable(gui.getText("playingStateOneUp"));
    controller.addDrawable(gui.getText("playingStateHiScore"));
    controller.addDrawable(gui.getText("playingStatePepper"));
    controller.addDrawable(gui.getText("playingStateScore"));
    controller.addDrawable(gui.getText("playingStateTopScore"));
    controller.addDrawable(gui.getText("playingStateLives"));
    controller.addDrawable(gui.getText("playingStateLevel"));
    controller.addDrawable(gameInfo->curtains[0]);
    controller.addDrawable(gameInfo->curtains[1]);
}

void NormalStatePlaying::react(const ExecuteEvent &event)
{
    checkMainMusic();

    auto &map = gameInfo->maps[gameInfo->currentMap];

    if (gameInfo->bonus->intersectsWith(*gameInfo->player))
    {
        gameInfo->bonus->has_been_claimed();
        addPoints(gameInfo->bonus->get_points());
        gameInfo->pepperCounter.changePepper(1);
    }

    static std::set<int> initialPositions;
    for (auto it = gameInfo->enemies.begin(); it != gameInfo->enemies.end(); ++it)
    {
        const auto &enemy = *it;

        if (!enemy->isSurfing() && !enemy->isPeppered() && gameInfo->player->intersectsWith(*enemy)) 
        {
#if true
            if (gameInfo->livesCounter.hasLives())
            {
                transit<DeadStatePlaying>(std::bind(&NormalStatePlaying::changeGameInfo, this));
                return;
            }
#endif
        }
        else if (enemy->completelyDead())
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<> spawnsDis(0, map->enemy_spawns.size() - 1);
            static std::uniform_int_distribution<> offsetDis(2, 4);

            auto enemySpawnsIt = map->enemy_spawns.begin();

            int initPos;
            do
            {
                initPos = spawnsDis(gen);
            } while (initialPositions.find(initPos) != initialPositions.end());

            initialPositions.insert(initPos);

            std::advance(enemySpawnsIt, initPos);
            const auto &initialTilePos = (*enemySpawnsIt).second;
            const auto &initialTile = map->tile_data[initialTilePos.x][initialTilePos.y];
            spawnEnemy(enemy->getType(), *initialTile, offsetDis(gen));

            it = gameInfo->enemies.erase(it);
            --it;

            controller.addDrawable(gameInfo->enemies.back());
        }
    }
    initialPositions.clear();

    ingredientCollision();

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

    gameInfo->bonus->update(event.deltaT);

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
    Audio::stopBackground();
    Audio::play(Audio::Track::DIE);

    controller.restartTimer();
    gameInfo->livesCounter.changeLives(-1);
    gameInfo->player->die();
}

void DeadStatePlaying::react(const ExecuteEvent &event)
{
    if (BurgerTimeStateMachine::timedStateReact(4))
    {
        if (!gameInfo->livesCounter.hasLives())
        {
            transit<GameOverStatePlaying>(std::bind(&DeadStatePlaying::changeGameInfo, this));
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

        ingredientCollision();

        gameInfo->player->update(event.deltaT);

        for (auto &ingredient : map->ing_data)
        {
            ingredient.update(event.deltaT);
        }
    }
}


void WinStatePlaying::entry()
{
    Audio::stopBackground();
    Audio::play(Audio::Track::WIN);
    
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
        Audio::play(Audio::Track::LEVEL_INTRO);
        gameInfo->levelCounter.addLevel(1);

        transit<GameReadyScreenState>(std::bind(&WinStatePlaying::changeGameInfo, this));
        // transit<EnterHighscoreState>(std::bind(&EnterHighscoreState::setHighScore, 999999));
    }
    else
    {
        gameInfo->player->update(event.deltaT);
    }
}
