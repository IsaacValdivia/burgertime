#include "Enemy.hpp"
#include "AI.hpp"

#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>

const Enemy::SpriteStateMachine Enemy::sausage_sprite_state_machine[] = {
    // SAUSAGE_DOWNSTAIRS_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_2, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_DOWNSTAIRS_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_2, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_LEFT_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::SAUSAGE_LEFT_1, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_2, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_2, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_LEFT_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::SAUSAGE_LEFT_2, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_UPSTAIRS_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_2, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_UPSTAIRS_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_2, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_CRUSHED_1
    dying_sprite_duration,
    {
        BtSprites::Sprite::SAUSAGE_CRUSHED_1, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_2, // DIE
    },
    // SAUSAGE_CRUSHED_2
    dying_sprite_duration,
    {
        BtSprites::Sprite::SAUSAGE_CRUSHED_2, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_3, // DIE
    },
    // SAUSAGE_CRUSHED_3
    dying_sprite_duration,
    {
        BtSprites::Sprite::SAUSAGE_CRUSHED_3, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_4, // DIE
    },
    // SAUSAGE_CRUSHED_4
    dying_sprite_duration,
    {
        BtSprites::Sprite::SAUSAGE_CRUSHED_4, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_4, // DIE
    },
    // SAUSAGE_PEPPER_2
    pepper_sprite_animation,
    {
        BtSprites::Sprite::SAUSAGE_PEPPER_2, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_PEPPER_1
    pepper_sprite_animation,
    {
        BtSprites::Sprite::SAUSAGE_PEPPER_1, // NONE
        BtSprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BtSprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BtSprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BtSprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::SAUSAGE_PEPPER_2, // PEPPER
        BtSprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
};

const Enemy::SpriteStateMachine Enemy::pickle_sprite_state_machine[] = {
    // PICKLE_DOWNSTAIRS_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // NONE
        BtSprites::Sprite::PICKLE_LEFT_1, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_2, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_DOWNSTAIRS_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_2, // NONE
        BtSprites::Sprite::PICKLE_LEFT_1, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_LEFT_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::PICKLE_LEFT_1, // NONE
        BtSprites::Sprite::PICKLE_LEFT_2, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_2, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_LEFT_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::PICKLE_LEFT_2, // NONE
        BtSprites::Sprite::PICKLE_LEFT_1, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_UPSTAIRS_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // NONE
        BtSprites::Sprite::PICKLE_LEFT_1, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_2, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_UPSTAIRS_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::PICKLE_UPSTAIRS_2, // NONE
        BtSprites::Sprite::PICKLE_LEFT_1, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_CRUSHED_1
    dying_sprite_duration,
    {
        BtSprites::Sprite::PICKLE_CRUSHED_1, // NONE
        BtSprites::Sprite::PICKLE_LEFT_1, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_2, // DIE
    },
    // PICKLE_CRUSHED_2
    dying_sprite_duration,
    {
        BtSprites::Sprite::PICKLE_CRUSHED_2, // NONE
        BtSprites::Sprite::PICKLE_LEFT_1, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_3, // DIE
    },
    // PICKLE_CRUSHED_3
    dying_sprite_duration,
    {
        BtSprites::Sprite::PICKLE_CRUSHED_3, // NONE
        BtSprites::Sprite::PICKLE_LEFT_1, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_4, // DIE
    },
    // PICKLE_CRUSHED_4
    dying_sprite_duration,
    {
        BtSprites::Sprite::PICKLE_CRUSHED_4, // NONE
        BtSprites::Sprite::PICKLE_LEFT_1, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_4, // DIE
    },
    // PICKLE_PEPPER_2
    pepper_sprite_animation,
    {
        BtSprites::Sprite::PICKLE_PEPPER_2, // NONE
        BtSprites::Sprite::PICKLE_LEFT_1, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_PEPPER_1
    pepper_sprite_animation,
    {
        BtSprites::Sprite::PICKLE_PEPPER_1, // NONE
        BtSprites::Sprite::PICKLE_LEFT_1, // LEFT
        BtSprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BtSprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BtSprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PICKLE_PEPPER_2, // PEPPER
        BtSprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
};

const Enemy::SpriteStateMachine Enemy::egg_sprite_state_machine[] = {
    // EGG_DOWNSTAIRS_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // NONE
        BtSprites::Sprite::EGG_LEFT_1, // LEFT
        BtSprites::Sprite::EGG_LEFT_1, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_1, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_2, // DOWN
        BtSprites::Sprite::EGG_PEPPER_1, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_DOWNSTAIRS_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::EGG_DOWNSTAIRS_2, // NONE
        BtSprites::Sprite::EGG_LEFT_1, // LEFT
        BtSprites::Sprite::EGG_LEFT_1, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_1, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::EGG_PEPPER_1, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_LEFT_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::EGG_LEFT_1, // NONE
        BtSprites::Sprite::EGG_LEFT_2, // LEFT
        BtSprites::Sprite::EGG_LEFT_2, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_1, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::EGG_PEPPER_1, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_LEFT_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::EGG_LEFT_2, // NONE
        BtSprites::Sprite::EGG_LEFT_1, // LEFT
        BtSprites::Sprite::EGG_LEFT_1, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_1, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::EGG_PEPPER_1, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_UPSTAIRS_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::EGG_UPSTAIRS_1, // NONE
        BtSprites::Sprite::EGG_LEFT_1, // LEFT
        BtSprites::Sprite::EGG_LEFT_1, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_2, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::EGG_PEPPER_1, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_UPSTAIRS_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::EGG_UPSTAIRS_2, // NONE
        BtSprites::Sprite::EGG_LEFT_1, // LEFT
        BtSprites::Sprite::EGG_LEFT_1, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_1, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::EGG_PEPPER_1, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_CRUSHED_1
    dying_sprite_duration,
    {
        BtSprites::Sprite::EGG_CRUSHED_1, // NONE
        BtSprites::Sprite::EGG_LEFT_1, // LEFT
        BtSprites::Sprite::EGG_LEFT_1, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_1, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::EGG_PEPPER_1, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_2, // DIE
    },
    // EGG_CRUSHED_2
    dying_sprite_duration,
    {
        BtSprites::Sprite::EGG_CRUSHED_2, // NONE
        BtSprites::Sprite::EGG_LEFT_1, // LEFT
        BtSprites::Sprite::EGG_LEFT_1, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_1, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::EGG_PEPPER_1, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_3, // DIE
    },
    // EGG_CRUSHED_3
    dying_sprite_duration,
    {
        BtSprites::Sprite::EGG_CRUSHED_3, // NONE
        BtSprites::Sprite::EGG_LEFT_1, // LEFT
        BtSprites::Sprite::EGG_LEFT_1, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_1, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::EGG_PEPPER_1, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_4, // DIE
    },
    // EGG_CRUSHED_4
    dying_sprite_duration,
    {
        BtSprites::Sprite::EGG_CRUSHED_4, // NONE
        BtSprites::Sprite::EGG_LEFT_1, // LEFT
        BtSprites::Sprite::EGG_LEFT_1, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_1, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::EGG_PEPPER_1, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_4, // DIE
    },
    // EGG_PEPPER_2
    pepper_sprite_animation,
    {
        BtSprites::Sprite::EGG_PEPPER_2, // NONE
        BtSprites::Sprite::EGG_LEFT_1, // LEFT
        BtSprites::Sprite::EGG_LEFT_1, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_1, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::EGG_PEPPER_1, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_PEPPER_1
    pepper_sprite_animation,
    {
        BtSprites::Sprite::EGG_PEPPER_1, // NONE
        BtSprites::Sprite::EGG_LEFT_1, // LEFT
        BtSprites::Sprite::EGG_LEFT_1, // RIGHT
        BtSprites::Sprite::EGG_UPSTAIRS_1, // UP
        BtSprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::EGG_PEPPER_2, // PEPPER
        BtSprites::Sprite::EGG_CRUSHED_1, // DIE
    },
};

void Enemy::move(float &move_x, float &move_y, float delta_t) {
    move_x = 0;
    move_y = 0;

    switch (direction) {
        case Direction::LEFT:

            new_action = LEFT;
            move_x = -x_walking_speed * delta_t;

            break;
        case Direction::RIGHT:

            new_action = RIGHT;
            move_x = x_walking_speed * delta_t;

            break;
        case Direction::UP:

            new_action = UP;
            move_y = -y_walking_speed * delta_t;

            break;
        case Direction::DOWN:

            new_action = DOWN;
            move_y = y_walking_speed * delta_t;

            break;
        default:
            break;
    }
}

void Enemy::random_move(const float delta_t, const Tile &current) {

    Direction backup_dir = direction;

    std::set<Direction> available_dirs = map->available_from_direction(current, backup_dir);
    std::vector<Direction> posible_dirs;

    if (backup_dir != Direction::RIGHT &&
            available_dirs.find(Direction::LEFT) != available_dirs.end()) {

        posible_dirs.push_back(Direction::LEFT);
    }

    if (backup_dir != Direction::LEFT &&
            available_dirs.find(Direction::RIGHT) != available_dirs.end()) {

        posible_dirs.push_back(Direction::RIGHT);
    }

    if (backup_dir != Direction::UP &&
            available_dirs.find(Direction::DOWN) != available_dirs.end()) {

        posible_dirs.push_back(Direction::DOWN);
    }

    if (backup_dir != Direction::DOWN &&
            available_dirs.find(Direction::UP) != available_dirs.end()) {

        posible_dirs.push_back(Direction::UP);
    }

    if (posible_dirs.size() > 0) {
        int rand_num = rand() % posible_dirs.size();

        direction = posible_dirs.at(rand_num);
    }
}

Enemy::Enemy(const Type &type, const sf::Vector2f &init_pos,
             const std::shared_ptr<Map> map, const AI &ia,
             const Direction initial_direction,
             const std::function<void(unsigned int)> &points_added, bool random_sometimes)
    : Actor(init_pos, sausage_sprite_state_machine[0].sprites[NONE],
            sausage_sprite_state_machine[0].sprites[NONE], map),
      type(type),
      last_action(NONE),
      acc_delta_t_pepper(0),
      ia(ia),
      initial_direction(initial_direction),
      a_star_direction(Direction::LEFT),
      a_star_tile(nullptr),
      initial_movement(true),
      totally_dead(false),
      after_dead(false),
      points_added(points_added),
      random_sometimes(random_sometimes) {

    switch (get_type()) {
        case Enemy::Type::SAUSAGE:
            sprite_state_machine = sausage_sprite_state_machine;
            dead_points = 100;
            break;
        case Enemy::Type::PICKLE:
            sprite_state_machine = pickle_sprite_state_machine;
            dead_points = 200;
            break;
        case Enemy::Type::EGG:
            sprite_state_machine = egg_sprite_state_machine;
            dead_points = 300;
            break;
    }

    BtSprites::update_sprite(sprite, sprite_state_machine[0].sprites[NONE]);
    current_sprite = sprite_state_machine[0].sprites[NONE];
    first_sprite = current_sprite;
}

void Enemy::pepper() {
    if (!Audio::is_playing(Audio::Track::PEPPERED)) {
        Audio::play(Audio::Track::PEPPERED);
    }

    acc_delta_t_pepper = 0;
    last_action = PEPPER;
}

void Enemy::start_surfing(nod::connection &&ingredient_moving_con,
                          nod::connection &&stop_surfing_con, const int dead_points) {

    Audio::play(Audio::Track::ENEMY_FALL);

    this->dead_points = dead_points;

    ingredient_moving_connection = std::make_unique<nod::connection>(
                                       std::move(ingredient_moving_con));
    stop_surfing_connection = std::make_unique<nod::connection>(std::move(
                                  stop_surfing_con));
}

void Enemy::stop_surfing() {
    ingredient_moving_connection->disconnect();
    stop_surfing_connection->disconnect();
    ingredient_moving_connection = nullptr;
    stop_surfing_connection = nullptr;
    die();
}

bool Enemy::is_peppered() const {
    return last_action == PEPPER;
}

void Enemy::die() {
    Actor::die();

    Audio::play(Audio::Track::ENEMY_CRUSHED);
}

bool Enemy::is_surfing() const {
    return ingredient_moving_connection != nullptr;
}

Enemy::Type Enemy::get_type() const {
    return type;
}

bool Enemy::completely_dead() const {
    return totally_dead;
}

void Enemy::move_by_signal(const float y) {
    sprite.setPosition(sprite.getPosition().x, y);
}

void Enemy::update(const float delta_t) {
    acc_delta_t += delta_t;
    acc_delta_t_pepper += delta_t;

    if (ingredient_moving_connection != nullptr) {
        return;
    }

    new_action = NONE;

    float animation_duration;

    if (!after_dead) {
        animation_duration = sprite_state_machine
                             [current_sprite - first_sprite].sprite_duration;
    }

    // DIE
    if (!is_alive()) {
        new_action = DIE;

        if (after_dead) {
            if (acc_delta_t >= after_dead_sprite_duration) {
                totally_dead = true;
            }
            return;
        }

        if (current_sprite == sprite_state_machine[
                    current_sprite - first_sprite].sprites[new_action] &&
                acc_delta_t >= animation_duration) {

            if (dead_points > 0) {
                after_dead = true;

                acc_delta_t = 0;

                direction = Direction::LEFT;
                mirror();

                points_added(dead_points);

                BtSprites::update_sprite(sprite,
                                         BtSprites::get_sprite_points(dead_points));
            }
            else {
                totally_dead = true;

                return;
            }

        }
    }
    // PEPPER
    else if (last_action == PEPPER && acc_delta_t_pepper < pepper_duration) {
        new_action = PEPPER;

        a_star_tile = nullptr;
    }
    // A*/MOVE
    else {
        acc_delta_t_pepper = 0;

        float move_x;
        float move_y;

        if (map->out_of_map(*this) && initial_movement) {
            direction = initial_direction;

            move(move_x, move_y, delta_t);
            sprite.move(move_x, move_y);
        }
        else {
            initial_movement = false;

            Direction backup_dir = direction;

            std::vector<std::shared_ptr<Tile>> actors_tiles = map->entity_on_tiles(*this);

            const std::shared_ptr<Tile> t = actors_tiles[0];

            bool a_start_called = false;

            for (auto tile : actors_tiles) {
                if (a_star_tile && *tile == *a_star_tile) {
                    a_start_called = true;
                }
            }

            if (!a_start_called && t->is_connector()) {
                int rand_num = rand() % 100;

                float goal_distance = ia.distance_to_goal(t);

                goal_distance /= AI::MAX_DISTANCE_BETWEEN_TILES;
                goal_distance *= 100;

                goal_distance /= rand_mov_prob_normalizer;

                if (rand_num > goal_distance && random_sometimes) {
                    fprintf(stderr, "RANDOM");
                    random_move(delta_t, *t);
                }
                else {
                    direction = ia.get_next_move(t);
                }

                a_star_direction = direction;
                a_star_tile = t;
            }
            else {
                direction = a_star_direction;
            }

            for (auto tile : actors_tiles) {
                map->set_enemy_on_tile(this, tile);
            }

            move(move_x, move_y, delta_t);
            // Want to move and can.
            if (map->can_entity_move(move_x, move_y, *this)) {
                sprite.move(move_x, move_y);
            }
            // Want to move but can't.
            else {
                direction = backup_dir;

                move(move_x, move_y, delta_t);

                if (map->can_entity_move(move_x, move_y, *this)) {
                    sprite.move(move_x, move_y);
                }
                else {
                    if (direction == Direction::LEFT) {
                        direction = Direction::RIGHT;
                    }
                    else {
                        direction = Direction::LEFT;
                    }

                    a_star_direction = direction;
                    a_star_tile = nullptr;

                    move(move_x, move_y, delta_t);

                    if (map->can_entity_move(move_x, move_y, *this)) {
                        sprite.move(move_x, move_y);
                    }
                    else {
                        fprintf(stderr, "ENEMY ERROR\n");
                    }
                }
            }
        }
    }

    // Set new sprite.

    if (acc_delta_t > animation_duration || new_action != last_action) {
        acc_delta_t = 0;

        current_sprite = sprite_state_machine[current_sprite - first_sprite].sprites[new_action];

        mirror();

        BtSprites::update_sprite(sprite, current_sprite);
    }

    last_action = new_action;
}
