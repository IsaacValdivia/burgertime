#include "PlayingStateMachine.hpp"

#include "Audio.hpp"
#include "BurgerTimeStateMachine.hpp"
#include "Enemy.hpp"
#include "HighScores.hpp"
#include "InputSystem.hpp"
#include "AI.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <random>
#include <set>

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

uint32_t PlayingStateMachine::ScoreCounter::get_score() const {
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
                        std::to_string(current_level), 3), sf::Vector2u(802, 860),
                    sf::Vector2f(0.5, 0.5), sf::Color::White);
}

FSM_INITIAL_STATE(PlayingStateMachine, EnterStatePlaying)

BurgerTimeController &PlayingStateMachine::controller = BurgerTimeController::get();
GUI &PlayingStateMachine::gui = GUI::get();

void PlayingStateMachine::add_pepper(const sf::Vector2f &launch_position,
                                     Direction direction) {

    if (current_state_ptr->game_info->pepper_counter.has_pepper()) {
        Audio::play(Audio::Track::PEPPER);

        current_state_ptr->game_info->pepper_counter.change_pepper(-1);
        current_state_ptr->delete_pepper();
        current_state_ptr->game_info->pepper = std::make_shared<Pepper>(
                launch_position, direction,
                std::bind(&PlayingStateMachine::delete_pepper, this));

        controller.add_drawable(current_state_ptr->game_info->pepper);
    }
}

bool PlayingStateMachine::has_pepper() const {
    return current_state_ptr->game_info->pepper_counter.has_pepper();
}

void PlayingStateMachine::add_player_and_enemies() {
    game_info->enemies.clear();
    auto &map = game_info->maps[game_info->current_map];

    const auto &player_spawn_tile = map->get_chef_initial_tile();

    sf::Vector2f init_pos = player_spawn_tile->get_position();
    init_pos.y -= player_spawn_tile->get_height();
    game_info->player = std::make_shared<Player>(init_pos, map,
                        std::bind(&PlayingStateMachine::add_pepper, this,
                                  std::placeholders::_1, std::placeholders::_2),
                        std::bind(&PlayingStateMachine::has_pepper, this)
                                                );

    game_info->ai = std::make_shared<AI>(map, player_spawn_tile);

    float offset = 1;
    for (const auto &enemy_spawn : map->get_enemies_spawns()) {
        spawn_enemy(static_cast<Enemy::Type>(enemy_spawn.first), *enemy_spawn.second, offset);
        offset += 1.2;
    }
}

void PlayingStateMachine::spawn_enemy(const Enemy::Type &type,
                                      const Tile &initial_tile, float offset) {

    auto &map = game_info->maps[game_info->current_map];
    // TODO: ia
    game_info->player->connect_player_moved(std::bind(&AI::set_goal_tile,
                                            game_info->ai,
                                            std::placeholders::_1));

    // game_info->player->connect_player_moved(std::bind(&AI::set_goal_tile,
    // &game_info->ias.back(), std::placeholders::_1));

    auto initial_pos = initial_tile.get_position();
    Direction initial_dir;
    if (abs(game_info->curtains[0]->getPosition().x - initial_pos.x) <
            abs(game_info->curtains[1]->getPosition().x - initial_pos.x)) {

        initial_dir = Direction::RIGHT;
        initial_pos.x -= offset * 5 * Tile::TILE_WIDTH;
    }
    else {
        initial_dir = Direction::LEFT;
        initial_pos.x += offset * 5 * Tile::TILE_WIDTH;
    }
    initial_pos.y -= initial_tile.get_height();

    // sf::Vector2
    game_info->enemies.push_back(std::make_shared<Enemy>(type, initial_pos,
                                 map, *game_info->ai, initial_dir,
                                 std::bind(&PlayingStateMachine::add_points,
                                           this, std::placeholders::_1)));
}


void PlayingStateMachine::delete_pepper() {
    current_state_ptr->game_info->pepper = nullptr;
}

void PlayingStateMachine::change_game_info() {
    current_state_ptr->set_game_info(std::move(game_info));
}

void PlayingStateMachine::set_game_info(std::unique_ptr<GameInfo> new_game_info) {
    game_info = std::move(new_game_info);
}

void PlayingStateMachine::ingredient_collision() {
    auto &map = game_info->maps[game_info->current_map];
    for (auto &ingredient : map->get_ing_data()) {
        int enemies_surfing = 0;

        if (ingredient.is_falling()) {
            const auto tiles = map->entity_on_tiles(ingredient);
            if (tiles.size() > 1) {
                if (tiles[1]->is_steppable_hor()) {
                    ingredient.land(tiles[1]->get_position().y
                                    + (Tile::TILE_HEIGHT - 8), Ingredient::FLOOR);
                }
                else if (tiles[1]->is_basket() || tiles[1]->is_basket_edge()) {
                    ingredient.land(tiles[1]->get_position().y
                                    + (Tile::TILE_HEIGHT - 12),
                                    Ingredient::STATIC_ING_BASKET);
                }
            }

            for (auto &other : map->get_ing_data()) {
                if (&other != &ingredient) {
                    if (other.intersects_with(ingredient) && (other.is_idle() ||
                            other.is_static())) {

                        add_points(50);
                        auto state = other.is_static() ?
                                     Ingredient::STATIC_ING_BASKET :
                                     Ingredient::INGREDIENT;

                        // other.land(tiles[1]->get_position().y +
                        // 10, Ingredient::INGREDIENT);
                        // std::cout << "other state " << other.state << std::endl;

                        ingredient.land(other.get_collision_shape().top -
                                        (Tile::TILE_HEIGHT - 8), state);

                        other.drop();
                        break;
                    }
                }
            }

            for (auto &enemy : game_info->enemies) {
                if (ingredient.intersects_with(*enemy) && enemy->is_alive()) {

                    if (ingredient.get_collision_shape().top <
                            enemy->get_collision_shape().top) {

                        enemy->die();
                    }
                }
            }
        }

        for (auto &enemy : game_info->enemies) {
            if (ingredient.intersects_with(*enemy) &&
                    ingredient.get_collision_shape().top >=
                    enemy->get_collision_shape().top) {

                enemies_surfing++;
            }
        }

        if (ingredient.test_static()) {
            game_info->current_ingredients++;
        }

        if (game_info->player->going_x_direction()) {
            if (ingredient.stepped(game_info->player->get_collision_shape(),
                                   1 + enemies_surfing * 2)) {

                bool first_surfer = true;
                int surf_points = std::pow(2, enemies_surfing - 1) * 500;

                Audio::play(Audio::Track::BURGER_GOING_DOWN);
                add_points(50);

                for (auto &enemy : game_info->enemies) {
                    if (!enemy->is_surfing() && ingredient.intersects_with(*enemy)
                            && ingredient.get_collision_shape().top >=
                            enemy->get_collision_shape().top) {

                        auto connections = ingredient.connect_enemy_surfer(
                                               std::bind(&Enemy::move_by_signal,
                                                         enemy,
                                                         std::placeholders::_1),
                                               std::bind(&Enemy::stop_surfing,
                                                         enemy));
                        if (first_surfer) {
                            enemy->start_surfing(std::move(connections.first),
                                                 std::move(connections.second),
                                                 surf_points);

                            first_surfer = false;
                        }
                        else {
                            enemy->start_surfing(std::move(connections.first),
                                                 std::move(connections.second),
                                                 0);
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
        current_state_ptr->game_info->points_to_extra_life =
            20000 - current_state_ptr->game_info->points_to_extra_life;
    }
}

uint32_t PlayingStateMachine::get_current_score() {
    return current_state_ptr->game_info->score_counter.get_score();
}

void EnterStatePlaying::entry() {
    Audio::play(Audio::Track::LEVEL_INTRO);

    controller.clear_screen();
    game_info = std::unique_ptr<GameInfo>(new GameInfo);

    game_info->has_just_entered = true;
    game_info->current_map = 0;
    game_info->current_ingredients = 0;
    game_info->points_to_extra_life = 20000;

    game_info->curtains[0] = std::make_shared<sf::RectangleShape>();
    game_info->curtains[0]->setFillColor(sf::Color::Black);
    game_info->curtains[0]->setPosition(sf::Vector2f(0, 0));
    game_info->curtains[0]->setSize(sf::Vector2f(2 * Tile::TILE_WIDTH,
                                    WINDOW_HEIGHT));

    game_info->curtains[1] = std::make_shared<sf::RectangleShape>();
    game_info->curtains[1]->setFillColor(sf::Color::Black);

    game_info->curtains[1]->setPosition(sf::Vector2f(WINDOW_WIDTH - 2 *
                                        Tile::TILE_WIDTH, 0));

    game_info->curtains[1]->setSize(sf::Vector2f(2 * Tile::TILE_WIDTH,
                                    WINDOW_HEIGHT));

    gui.create_text("playingStateOneUp", "1UP", sf::Vector2u(150, 20),
                    sf::Vector2f(0.5, 0.5), sf::Color::Red);

    gui.create_text("playingStateHiScore", "HI-SCORE", sf::Vector2u(300, 20),
                    sf::Vector2f(0.5, 0.5), sf::Color::Red);

    game_info->pepper_text = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*game_info->pepper_text,
                                  BtSprites::Sprite::PEPPER);

    game_info->pepper_text->setPosition(780 * WINDOW_WIDTH / 1000,
                                        16 * WINDOW_HEIGHT / 1000);

    game_info->pepper_text->setScale(2, 2);

    game_info->lives_sprite = std::make_shared<sf::Sprite>();

    BtSprites::set_initial_sprite(*game_info->lives_sprite,
                                  BtSprites::Sprite::LIVES);

    game_info->lives_sprite->setPosition(80 * WINDOW_WIDTH / 1000,
                                         815 * WINDOW_HEIGHT / 1000);

    game_info->lives_sprite->setScale(2, 2);

    game_info->level_sprite = std::make_shared<sf::Sprite>();

    BtSprites::set_initial_sprite(*game_info->level_sprite,
                                  BtSprites::Sprite::MINI_BURGER_1);

    game_info->level_sprite->setPosition(880 * WINDOW_WIDTH / 1000,
                                         815 * WINDOW_HEIGHT / 1000);

    game_info->level_sprite->setScale(2, 2);


    std::set<std::string> map_stems;
    for (const auto &map_file : fs::directory_iterator(MAPS_FOLDER)) {
        if (map_file.is_regular_file()) {
            map_stems.insert(MAPS_FOLDER + std::string("/") +
                             map_file.path().stem().string());
        }
    }
    std::vector<std::string> map_names(map_stems.begin(), map_stems.end());
    std::sort(map_names.begin(), map_names.end());

    for (const auto &map_name : map_names) {
        game_info->maps.push_back(std::make_shared<Map>(map_name));
    }
}

void EnterStatePlaying::react(const ExecuteEvent &event) {
    transit<GameReadyScreenState>(std::bind(&EnterStatePlaying::change_game_info,
                                            this));
}

void GameReadyScreenState::entry() {
    controller.clear_screen();

    auto text = gui.create_text("gameReadyText", "GAME READY",
                                sf::Vector2u(250, 500), sf::Vector2f(0.8, 0.8));

    add_player_and_enemies();

    controller.add_drawable(text);
    controller.restart_timer();
}

void GameReadyScreenState::react(const ExecuteEvent &) {
    if (BurgerTimeStateMachine::timed_state_react(1)) {
        // TODO: change
        transit<NormalStatePlaying>(std::bind(
                                        &GameReadyScreenState::change_game_info,
                                        this));

        // transit<EnterHighscoreState>(std::bind(
        //&EnterHighscoreState::set_high_score, 999999));
    }
}

void NormalStatePlaying::check_main_music() {
    if (!main_music_played) {
        if (game_info->has_just_entered) {

            auto elapsed_time = controller.get_elapsed_time();

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
    controller.clear_screen();
    main_music_played = false;

    auto &map = game_info->maps[game_info->current_map];
    for (auto &ingredient : map->get_ing_data()) {
        ingredient.reset();
    }

    const auto &item_spawn_tile = map->get_item_initial_tile();

    sf::Vector2f init_pos = item_spawn_tile->get_position();
    // init_pos.y -= item_spawn_tile->height;

    BtSprites::Sprite init_sprite;
    int points;
    switch (map->get_item_type()) {
        case Map::ICE_CREAM:
            init_sprite = BtSprites::Sprite::ICE_CREAM;
            points = 500;
            break;
        case Map::COFFEE:
            init_sprite = BtSprites::Sprite::COFFEE;
            points = 1000;
            break;
        case Map::FRIES:
            init_sprite = BtSprites::Sprite::FRIES;
            points = 1500;
            break;
    }

    game_info->bonus = std::make_shared<Bonus>(init_pos, init_sprite, points);

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

    static std::set<int> initial_positions;
    for (auto it = game_info->enemies.begin();
            it != game_info->enemies.end(); ++it) {

        const auto &enemy = *it;

        if (enemy->is_alive() && !enemy->is_surfing() && !enemy->is_peppered() &&
                game_info->player->intersects_with(*enemy)) {
#if true
            if (game_info->lives_counter.has_lives()) {
                transit<DeadStatePlaying>(std::bind(
                                              &NormalStatePlaying::change_game_info,
                                              this));
                return;
            }
#endif
        }
        else if (enemy->completely_dead()) {
            static std::random_device rd;
            static std::mt19937 gen(rd());

            static std::uniform_int_distribution<> spawns_dis(0,
                    map->get_enemies_spawns().size() - 1);

            static std::uniform_int_distribution<> offset_dis(2, 4);

            auto enemy_spawns_it = map->get_enemies_spawns().begin();

            int init_pos;
            do {
                init_pos = spawns_dis(gen);
            }
            while (initial_positions.find(init_pos) != initial_positions.end());

            initial_positions.insert(init_pos);

            std::advance(enemy_spawns_it, init_pos);
            const auto &initial_tile = (*enemy_spawns_it).second;

            spawn_enemy(enemy->get_type(), *initial_tile, offset_dis(gen));

            it = game_info->enemies.erase(it);
            --it;

            controller.add_drawable(game_info->enemies.back());
        }
    }
    initial_positions.clear();

    ingredient_collision();

    if (game_info->current_ingredients == map->get_ing_data().size()) {
        transit<WinStatePlaying>(std::bind(&NormalStatePlaying::change_game_info,
                                           this));
        return;
    }

    if (game_info->pepper) {
        for (const auto &enemy : game_info->enemies) {
            if (game_info->pepper->intersects_with(*enemy)) {
                enemy->pepper();
            }
        }
    }

    game_info->bonus->update(event.delta_t);

    game_info->player->update(event.delta_t);

    for (const auto &enemy : game_info->enemies) {
        enemy->update(event.delta_t);
    }

    for (auto &ingredient : map->get_ing_data()) {
        ingredient.update(event.delta_t);
    }

    if (game_info->pepper) {
        game_info->pepper->update(event.delta_t);
    }
}


void DeadStatePlaying::entry() {
    Audio::stop_background();
    Audio::play(Audio::Track::DIE);

    controller.restart_timer();
    game_info->lives_counter.change_lives(-1);
    game_info->player->die();
}

void DeadStatePlaying::react(const ExecuteEvent &event) {
    if (BurgerTimeStateMachine::timed_state_react(4)) {
        if (!game_info->lives_counter.has_lives()) {
            transit<GameOverStatePlaying>(std::bind(
                                              &DeadStatePlaying::change_game_info,
                                              this));
        }
        else {
            transit<GameReadyScreenState>(std::bind(
                                              &DeadStatePlaying::change_game_info,
                                              this));
        }

        // TODO: change
        // transit<EnterHighscoreState>(std::bind(&EnterHighscoreState::set_high_score, 999999));
    }
    else {
        auto &map = game_info->maps[game_info->current_map];

        ingredient_collision();

        game_info->player->update(event.delta_t);

        for (auto &ingredient : map->get_ing_data()) {
            ingredient.update(event.delta_t);
        }
    }
}

void WinStatePlaying::entry() {
    Audio::stop_background();
    Audio::play(Audio::Track::WIN);

    controller.restart_timer();
    game_info->player->win();
    game_info->current_map = (game_info->current_map + 1) % game_info->maps.size();
    game_info->current_ingredients = 0;
}

void WinStatePlaying::react(const ExecuteEvent &event) {
    if (BurgerTimeStateMachine::timed_state_react(4)) {
        // TODO: change
        Audio::play(Audio::Track::LEVEL_INTRO);
        game_info->level_counter.add_level(1);

        transit<GameReadyScreenState>(std::bind(
                                          &WinStatePlaying::change_game_info,
                                          this));

        // transit<EnterHighscoreState>(std::bind(
        // &EnterHighscoreState::set_high_score,
        // 999999));
    }
    else {
        game_info->player->update(event.delta_t);
    }
}
