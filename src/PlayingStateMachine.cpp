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

void PlayingStateMachine::PepperCounter::change_pepper(int change) {
    if (current_pepper + change >= 0) {
        current_pepper += change;
        gui.get_text("playingStatePepper").lock()->setString(
            GUI::fix_text_to_right(std::to_string(current_pepper), 3));
    }
}

bool PlayingStateMachine::PepperCounter::has_pepper() const {
    return current_pepper != 0;
}

PlayingStateMachine::PepperCounter::PepperCounter() : current_pepper(5) {
    gui.create_text("playingStatePepper", GUI::fix_text_to_right(
                        std::to_string(current_pepper), 3), sf::Vector2u(763, 48),
                    sf::Vector2f(0.5, 0.5), sf::Color::White);
}

void PlayingStateMachine::LivesCounter::change_lives(int change) {
    current_lives += change;
    gui.get_text("playingStateLives").lock()->setString(
        GUI::fix_text_to_right(std::to_string(current_lives), 3));
}

bool PlayingStateMachine::LivesCounter::has_lives() const {
    return current_lives != 0;
}

PlayingStateMachine::LivesCounter::LivesCounter() : current_lives(3) {
    gui.create_text("playingStateLives",
                    GUI::fix_text_to_right(std::to_string(current_lives), 3),
                    sf::Vector2u(1, 860), sf::Vector2f(0.5, 0.5), sf::Color::White);
}

void PlayingStateMachine::ScoreCounter::add_points(uint32_t points) {
    current_score += points;

    if (current_score > current_top_score) {

        current_top_score = current_score;

        gui.get_text("playingStateTopScore").lock()->setString(
            GUI::fix_text_to_right(std::to_string(current_score), MAX_SCORE_CHARS));
    }

    gui.get_text("playingStateScore").lock()->setString(
        GUI::fix_text_to_right(std::to_string(current_score), MAX_SCORE_CHARS));
}

uint32_t PlayingStateMachine::ScoreCounter::getScore() const {
    return current_score;
}

PlayingStateMachine::ScoreCounter::ScoreCounter() :
    current_score(0), current_top_score(HighScores().get_top_score()) {

    gui.create_text("playingStateScore", GUI::fix_text_to_right(
                        std::to_string(current_score), MAX_SCORE_CHARS),
                    sf::Vector2u(50, 48), sf::Vector2f(0.5, 0.5), sf::Color::White);

    gui.create_text("playingStateTopScore", GUI::fix_text_to_right(
                        std::to_string(current_top_score), MAX_SCORE_CHARS),
                    sf::Vector2u(300, 48), sf::Vector2f(0.5, 0.5), sf::Color::White);
}

void PlayingStateMachine::LevelCounter::add_level(uint32_t level) {
    current_level += level;

    gui.get_text("playingStateLevel").lock()->setString(GUI::fix_text_to_right(
                std::to_string(current_level), 3));
}

PlayingStateMachine::LevelCounter::LevelCounter() : current_level(1) {
    gui.create_text("playingStateLevel", GUI::fix_text_to_right(
                        std::to_string(current_level), 3),
                    sf::Vector2u(800, 860),
                    sf::Vector2f(0.5, 0.5), sf::Color::White);
}

FSM_INITIAL_STATE(PlayingStateMachine, EnterStatePlaying)

BurgerTimeController &PlayingStateMachine::controller = BurgerTimeController::get();
GUI &PlayingStateMachine::gui = GUI::get();

void PlayingStateMachine::add_pepper(const sf::Vector2f &launchPosition,
                                     Direction direction) {

    if (current_state_ptr->game_info->pepper_counter.has_pepper()) {
        Audio::play(Audio::Track::PEPPER);

        current_state_ptr->game_info->pepper_counter.change_pepper(-1);
        current_state_ptr->delete_pepper();
        current_state_ptr->game_info->pepper = std::make_shared<Pepper>(
                launchPosition, direction,
                std::bind(&PlayingStateMachine::delete_pepper, this));

        controller.add_drawable(current_state_ptr->game_info->pepper);
    }
    else {
        // TODO: exception
    }
}

bool PlayingStateMachine::has_pepper() const {
    return current_state_ptr->game_info->pepper_counter.has_pepper();
}

void PlayingStateMachine::add_player_and_enemies() {
    game_info->enemies.clear();
    auto &map = game_info->maps[game_info->current_map];

    const auto &playerSpawnTile = map->tile_data[map->chef_spawn.x][map->chef_spawn.y];

    sf::Vector2f initPos = playerSpawnTile->shape.getPosition();
    initPos.y -= playerSpawnTile->height;
    game_info->player = std::make_shared<Player>(initPos, map,
                        std::bind(&PlayingStateMachine::add_pepper, this, std::placeholders::_1, std::placeholders::_2),
                        std::bind(&PlayingStateMachine::has_pepper, this)
                                                );

    game_info->ai = std::make_shared<AI>(map, playerSpawnTile);

    float offset = 1;
    for (const auto &enemySpawn : map->enemy_spawns) {
        const auto &initialTile = map->tile_data[enemySpawn.second.x][enemySpawn.second.y];
        spawn_enemy(static_cast<Enemy::Type>(enemySpawn.first), *initialTile, offset);
        offset += 1.2;
    }
}

void PlayingStateMachine::spawn_enemy(const Enemy::Type &type, const Tile &initialTile, float offset) {
    auto &map = game_info->maps[game_info->current_map];
    // TODO: ia
    game_info->player->connect_player_moved(std::bind(&AI::setGoalTile, game_info->ai, std::placeholders::_1));
    // game_info->player->connect_player_moved(std::bind(&AI::setGoalTile, &game_info->ias.back(), std::placeholders::_1));

    auto initialPos = initialTile.shape.getPosition();
    Direction initialDir;
    if (abs(game_info->curtains[0]->getPosition().x - initialPos.x) < abs(game_info->curtains[1]->getPosition().x - initialPos.x)) {
        initialDir = Direction::RIGHT;
        initialPos.x -= offset * 5 * Tile::TILE_WIDTH;
    }
    else {
        initialDir = Direction::LEFT;
        initialPos.x += offset * 5 * Tile::TILE_WIDTH;
    }
    initialPos.y -= initialTile.height;

    // sf::Vector2
    const Enemy::SpriteStateMachine *enemySprites;

    switch (type) {
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

    game_info->enemies.push_back(std::make_shared<Enemy>(type, initialPos, enemySprites, map, *game_info->ai, initialDir, std::bind(&PlayingStateMachine::add_points, this, std::placeholders::_1)));
}


void PlayingStateMachine::delete_pepper() {
    current_state_ptr->game_info->pepper = nullptr;
}

void PlayingStateMachine::change_game_info() {
    current_state_ptr->set_game_info(std::move(game_info));
}

void PlayingStateMachine::set_game_info(std::unique_ptr<GameInfo> newGameInfo) {
    game_info = std::move(newGameInfo);
}

void PlayingStateMachine::ingredient_collision() {
    auto &map = game_info->maps[game_info->current_map];
    for (auto &ingredient : map->ing_data) {
        int enemiesSurfing = 0;

        if (ingredient.is_falling()) {
            const auto tiles = map->entityOnTiles(ingredient);
            if (tiles.size() > 1) {
                if (tiles[1]->isSteppableHor()) {
                    ingredient.land(tiles[1]->shape.getPosition().y + (Tile::TILE_HEIGHT - 8), Ingredient::FLOOR);
                }
                else if (tiles[1]->isBasket() || tiles[1]->isBasketEdge()) {
                    ingredient.land(tiles[1]->shape.getPosition().y + (Tile::TILE_HEIGHT - 12), Ingredient::STATIC_ING_BASKET);
                }
            }

            for (auto &other : map->ing_data) {
                if (&other != &ingredient) {
                    if (other.intersects_with(ingredient) && (other.is_idle() || other.is_static())) {
                        add_points(50);
                        auto state = other.is_static() ? Ingredient::STATIC_ING_BASKET : Ingredient::INGREDIENT;
                        // other.land(tiles[1]->shape.getPosition().y +
                        // 10, Ingredient::INGREDIENT);
                        // std::cout << "other state " << other.state << std::endl;
                        ingredient.land(other.get_collision_shape().top - (Tile::TILE_HEIGHT - 8), state);
                        other.drop();
                        break;
                    }
                }
            }

            for (auto &enemy : game_info->enemies) {
                if (ingredient.intersects_with(*enemy) && enemy->is_alive()) {
                    if (ingredient.get_collision_shape().top < enemy->get_collision_shape().top) {
                        enemy->die();
                    }
                }
            }
        }

        for (auto &enemy : game_info->enemies) {
            if (ingredient.intersects_with(*enemy) && ingredient.get_collision_shape().top >= enemy->get_collision_shape().top) {
                enemiesSurfing++;
            }
        }

        if (ingredient.test_static()) {
            game_info->current_ingredients++;
        }

        if (game_info->player->going_x_direction()) {
            if (ingredient.stepped(game_info->player->getCollisionShape(), 1 + enemiesSurfing * 2)) {
                bool firstSurfer = true;
                int surfPoints = std::pow(2, enemiesSurfing - 1) * 500;
                Audio::play(Audio::Track::BURGER_GOING_DOWN);
                add_points(50);
                for (auto &enemy : game_info->enemies) {
                    if (!enemy->is_surfing() && ingredient.intersects_with(*enemy) && ingredient.getCollisionShape().top >= enemy->getCollisionShape().top) {
                        auto connections = ingredient.connect_enemy_surfer(
                                               std::bind(&Enemy::move_by_signal, enemy, std::placeholders::_1),
                                               std::bind(&Enemy::stop_surfing, enemy));
                        if (firstSurfer) {
                            enemy->start_surfing(std::move(connections.first), std::move(connections.second), surfPoints);
                            firstSurfer = false;
                        }
                        else {
                            enemy->start_surfing(std::move(connections.first), std::move(connections.second), 0);
                        }

                    }
                }
            }
        }
    }
}

void PlayingStateMachine::add_points(unsigned int points) {
    current_state_ptr->game_info->score_counter.add_points(points);
    current_state_ptr->game_info->points_to_extra_life -= points;

    if (current_state_ptr->game_info->points_to_extra_life <= 0) {
        Audio::play(Audio::Track::ONE_UP);
        current_state_ptr->game_info->lives_counter.change_lives(1);
        current_state_ptr->game_info->points_to_extra_life = 20000 - current_state_ptr->game_info->points_to_extra_life;
    }
}

uint32_t PlayingStateMachine::get_current_score() {
    return current_state_ptr->game_info->score_counter.getScore();
}


void EnterStatePlaying::entry() {
    Audio::play(Audio::Track::LEVEL_INTRO);

    controller.clearScreen();
    game_info = std::unique_ptr<GameInfo>(new GameInfo);

    game_info->has_just_entered = true;
    game_info->current_map = 0;
    game_info->current_ingredients = 0;
    game_info->points_to_extra_life = 20000;

    game_info->curtains[0] = std::make_shared<sf::RectangleShape>();
    game_info->curtains[0]->setFillColor(sf::Color::Black);
    game_info->curtains[0]->setPosition(sf::Vector2f(0, 0));
    game_info->curtains[0]->setSize(sf::Vector2f(2 * Tile::TILE_WIDTH, WINDOW_HEIGHT));
    game_info->curtains[1] = std::make_shared<sf::RectangleShape>();
    game_info->curtains[1]->setFillColor(sf::Color::Black);
    game_info->curtains[1]->setPosition(sf::Vector2f(WINDOW_WIDTH - 2 * Tile::TILE_WIDTH, 0));
    game_info->curtains[1]->setSize(sf::Vector2f(2 * Tile::TILE_WIDTH, WINDOW_HEIGHT));

    gui.create_text("playingStateOneUp", "1UP", sf::Vector2u(150, 20), sf::Vector2f(0.5, 0.5), sf::Color::Red);
    gui.create_text("playingStateHiScore", "HI-SCORE", sf::Vector2u(300, 20), sf::Vector2f(0.5, 0.5), sf::Color::Red);

    game_info->pepper_text = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*game_info->pepper_text, BT_sprites::Sprite::PEPPER);
    game_info->pepper_text->setPosition(780 * WINDOW_WIDTH / 1000, 16 * WINDOW_HEIGHT / 1000);
    game_info->pepper_text->setScale(2, 2);

    game_info->lives_sprite = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*game_info->lives_sprite, BT_sprites::Sprite::LIVES);
    game_info->lives_sprite->setPosition(80 * WINDOW_WIDTH / 1000, 815 * WINDOW_HEIGHT / 1000);
    game_info->lives_sprite->setScale(2, 2);

    game_info->level_sprite = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*game_info->level_sprite, BT_sprites::Sprite::MINI_BURGER_1);
    game_info->level_sprite->setPosition(880 * WINDOW_WIDTH / 1000, 815 * WINDOW_HEIGHT / 1000);
    game_info->level_sprite->setScale(2, 2);


    std::set<std::string> mapStems;
    for (const auto &mapFile : fs::directory_iterator(MAPS_FOLDER)) {
        if (mapFile.is_regular_file()) {
            mapStems.insert(MAPS_FOLDER + std::string("/") + mapFile.path().stem().string());
        }
    }
    std::vector<std::string> mapNames(mapStems.begin(), mapStems.end());
    std::sort(mapNames.begin(), mapNames.end());

    for (const auto &mapName : mapNames) {
        game_info->maps.push_back(std::make_shared<Map>(mapName));
    }
}



void EnterStatePlaying::react(const ExecuteEvent &event) {
    transit<GameReadyScreenState>(std::bind(&EnterStatePlaying::change_game_info, this));
}


void GameReadyScreenState::entry() {
    controller.clearScreen();

    auto text = gui.create_text("gameReadyText", "GAME READY", sf::Vector2u(250, 500), sf::Vector2f(0.8, 0.8));
    add_player_and_enemies();

    controller.add_drawable(text);
    controller.restartTimer();
}

void GameReadyScreenState::react(const ExecuteEvent &) {
    if (BurgerTimeStateMachine::timed_state_react(1)) {
        // TODO: change
        transit<NormalStatePlaying>(std::bind(&GameReadyScreenState::change_game_info, this));
        // transit<EnterHighscoreState>(std::bind(&EnterHighscoreState::setHighScore, 999999));
    }
}


void NormalStatePlaying::check_main_music() {
    if (!main_music_played) {
        if (game_info->has_just_entered) {
            auto elapsed_time = controller.getElapsedTime();
            if (elapsed_time.asSeconds() >= 4) {
                main_music_played = true;
                game_info->has_just_entered = false;
                Audio::play(Audio::Track::MAIN);
            }
        }
        else {
            main_music_played = true;
            Audio::play(Audio::Track::MAIN);
        }
    }
}

void NormalStatePlaying::entry() {
    controller.clearScreen();
    main_music_played = false;

    auto &map = game_info->maps[game_info->current_map];
    for (auto &ingredient : map->ing_data) {
        ingredient.reset_steps();
        ingredient.fix_position_up();
    }

    const auto &itemSpawnTile = map->tile_data[map->item_spawn.second.x][map->item_spawn.second.y];

    sf::Vector2f initPos = itemSpawnTile->shape.getPosition();
    // initPos.y -= itemSpawnTile->height;

    BT_sprites::Sprite init_sprite;
    int points;
    switch (map->item_spawn.first) {
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

    game_info->bonus = std::make_shared<Bonus>(initPos, init_sprite, points);


    controller.add_drawable(game_info->maps[game_info->current_map]);
    controller.add_drawable(game_info->bonus);
    for (const auto &enemy : game_info->enemies) {
        controller.add_drawable(enemy);
    }
    controller.add_drawable(game_info->player);
    controller.add_drawable(game_info->pepper_text);
    controller.add_drawable(game_info->lives_sprite);
    controller.add_drawable(game_info->level_sprite);
    controller.add_drawable(gui.get_text("playingStateOneUp"));
    controller.add_drawable(gui.get_text("playingStateHiScore"));
    controller.add_drawable(gui.get_text("playingStatePepper"));
    controller.add_drawable(gui.get_text("playingStateScore"));
    controller.add_drawable(gui.get_text("playingStateTopScore"));
    controller.add_drawable(gui.get_text("playingStateLives"));
    controller.add_drawable(gui.get_text("playingStateLevel"));
    controller.add_drawable(game_info->curtains[0]);
    controller.add_drawable(game_info->curtains[1]);
}

void NormalStatePlaying::react(const ExecuteEvent &event) {
    check_main_music();

    auto &map = game_info->maps[game_info->current_map];

    if (game_info->bonus->intersects_with(*game_info->player)) {
        game_info->bonus->has_been_claimed();
        add_points(game_info->bonus->get_points());
        game_info->pepper_counter.change_pepper(1);
    }

    static std::set<int> initialPositions;
    for (auto it = game_info->enemies.begin(); it != game_info->enemies.end(); ++it) {
        const auto &enemy = *it;

        if (!enemy->is_surfing() && !enemy->is_peppered() && game_info->player->intersects_with(*enemy)) {
#if true
            if (game_info->lives_counter.has_lives()) {
                transit<DeadStatePlaying>(std::bind(&NormalStatePlaying::change_game_info, this));
                return;
            }
#endif
        }
        else if (enemy->completely_dead()) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<> spawnsDis(0, map->enemy_spawns.size() - 1);
            static std::uniform_int_distribution<> offsetDis(2, 4);

            auto enemySpawnsIt = map->enemy_spawns.begin();

            int initPos;
            do {
                initPos = spawnsDis(gen);
            }
            while (initialPositions.find(initPos) != initialPositions.end());

            initialPositions.insert(initPos);

            std::advance(enemySpawnsIt, initPos);
            const auto &initialTilePos = (*enemySpawnsIt).second;
            const auto &initialTile = map->tile_data[initialTilePos.x][initialTilePos.y];
            spawn_enemy(enemy->get_type(), *initialTile, offsetDis(gen));

            it = game_info->enemies.erase(it);
            --it;

            controller.add_drawable(game_info->enemies.back());
        }
    }
    initialPositions.clear();

    ingredient_collision();

    if (game_info->current_ingredients == map->ing_data.size()) {
        transit<WinStatePlaying>(std::bind(&NormalStatePlaying::change_game_info, this));
        return;
    }

    if (game_info->pepper) {
        for (const auto &enemy : game_info->enemies) {
            if (game_info->pepper->intersects_with(*enemy)) {
                // TODO: algo?
                enemy->pepper();
            }
        }
    }

    game_info->bonus->update(event.delta_t);

    game_info->player->update(event.delta_t);

    for (const auto &enemy : game_info->enemies) {
        enemy->update(event.delta_t);
    }

    for (auto &ingredient : map->ing_data) {
        ingredient.update(event.delta_t);
    }

    if (game_info->pepper) {
        game_info->pepper->update(event.delta_t);
    }
}


void DeadStatePlaying::entry() {
    Audio::stop_background();
    Audio::play(Audio::Track::DIE);

    controller.restartTimer();
    game_info->lives_counter.change_lives(-1);
    game_info->player->die();
}

void DeadStatePlaying::react(const ExecuteEvent &event) {
    if (BurgerTimeStateMachine::timed_state_react(4)) {
        if (!game_info->lives_counter.has_lives()) {
            transit<GameOverStatePlaying>(std::bind(&DeadStatePlaying::change_game_info, this));
        }
        else {
            transit<GameReadyScreenState>(std::bind(&DeadStatePlaying::change_game_info, this));
        }

        // TODO: change
        // transit<EnterHighscoreState>(std::bind(&EnterHighscoreState::setHighScore, 999999));
    }
    else {
        auto &map = game_info->maps[game_info->current_map];

        ingredient_collision();

        game_info->player->update(event.delta_t);

        for (auto &ingredient : map->ing_data) {
            ingredient.update(event.delta_t);
        }
    }
}


void WinStatePlaying::entry() {
    Audio::stop_background();
    Audio::play(Audio::Track::WIN);

    controller.restartTimer();
    game_info->player->win();
    game_info->current_map = (game_info->current_map + 1) % game_info->maps.size();
    game_info->current_ingredients = 0;
}

void WinStatePlaying::react(const ExecuteEvent &event) {
    if (BurgerTimeStateMachine::timed_state_react(4)) {
        // TODO: change
        Audio::play(Audio::Track::LEVEL_INTRO);
        game_info->level_counter.add_level(1);

        transit<GameReadyScreenState>(std::bind(&WinStatePlaying::change_game_info, this));
        // transit<EnterHighscoreState>(std::bind(&EnterHighscoreState::setHighScore, 999999));
    }
    else {
        game_info->player->update(event.delta_t);
    }
}
