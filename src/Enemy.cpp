#include "Enemy.hpp"
#include <iostream>

const Enemy::Sprite_state_machine Enemy::sausage_sprite_state_machine[] = {
    // SAUSAGE_DOWNSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_2, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_DOWNSTAIRS_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_2, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_LEFT_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_2, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_2, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_LEFT_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::SAUSAGE_LEFT_2, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_UPSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_2, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_UPSTAIRS_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_2, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_CRUSHED_1
    dying_sprite_duration,
    {
        BT_sprites::Sprite::SAUSAGE_CRUSHED_1, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_2, // DIE
    },
    // SAUSAGE_CRUSHED_2
    dying_sprite_duration,
    {
        BT_sprites::Sprite::SAUSAGE_CRUSHED_2, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_3, // DIE
    },
    // SAUSAGE_CRUSHED_3
    dying_sprite_duration,
    {
        BT_sprites::Sprite::SAUSAGE_CRUSHED_3, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_4, // DIE
    },
    // SAUSAGE_CRUSHED_4
    dying_sprite_duration,
    {
        BT_sprites::Sprite::SAUSAGE_CRUSHED_4, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_4, // DIE
    },
    // SAUSAGE_PEPPER_2
    pepper_sprite_animation,
    {
        BT_sprites::Sprite::SAUSAGE_PEPPER_2, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
    // SAUSAGE_PEPPER_1
    pepper_sprite_animation,
    {
        BT_sprites::Sprite::SAUSAGE_PEPPER_1, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::SAUSAGE_PEPPER_2, // PEPPER
        BT_sprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
    },
};

const Enemy::Sprite_state_machine Enemy::pickle_sprite_state_machine[] = {
    // PICKLE_DOWNSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_2, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_DOWNSTAIRS_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_2, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_LEFT_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PICKLE_LEFT_1, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_2, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_2, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_LEFT_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PICKLE_LEFT_2, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_UPSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_2, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_UPSTAIRS_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PICKLE_UPSTAIRS_2, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_CRUSHED_1
    dying_sprite_duration,
    {
        BT_sprites::Sprite::PICKLE_CRUSHED_1, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_2, // DIE
    },
    // PICKLE_CRUSHED_2
    dying_sprite_duration,
    {
        BT_sprites::Sprite::PICKLE_CRUSHED_2, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_3, // DIE
    },
    // PICKLE_CRUSHED_3
    dying_sprite_duration,
    {
        BT_sprites::Sprite::PICKLE_CRUSHED_3, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_4, // DIE
    },
    // PICKLE_CRUSHED_4
    dying_sprite_duration,
    {
        BT_sprites::Sprite::PICKLE_CRUSHED_4, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_4, // DIE
    },
    // PICKLE_PEPPER_2
    pepper_sprite_animation,
    {
        BT_sprites::Sprite::PICKLE_PEPPER_2, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_1, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
    // PICKLE_PEPPER_1
    pepper_sprite_animation,
    {
        BT_sprites::Sprite::PICKLE_PEPPER_1, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PICKLE_PEPPER_2, // PEPPER
        BT_sprites::Sprite::PICKLE_CRUSHED_1, // DIE
    },
};

const Enemy::Sprite_state_machine Enemy::egg_sprite_state_machine[] = {
    // EGG_DOWNSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_2, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_1, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_DOWNSTAIRS_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::EGG_DOWNSTAIRS_2, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_1, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_LEFT_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::EGG_LEFT_1, // NONE
        BT_sprites::Sprite::EGG_LEFT_2, // LEFT
        BT_sprites::Sprite::EGG_LEFT_2, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_1, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_LEFT_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::EGG_LEFT_2, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_1, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_UPSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_2, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_1, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_UPSTAIRS_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::EGG_UPSTAIRS_2, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_1, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_CRUSHED_1
    dying_sprite_duration,
    {
        BT_sprites::Sprite::EGG_CRUSHED_1, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_1, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_2, // DIE
    },
    // EGG_CRUSHED_2
    dying_sprite_duration,
    {
        BT_sprites::Sprite::EGG_CRUSHED_2, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_1, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_3, // DIE
    },
    // EGG_CRUSHED_3
    dying_sprite_duration,
    {
        BT_sprites::Sprite::EGG_CRUSHED_3, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_1, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_4, // DIE
    },
    // EGG_CRUSHED_4
    dying_sprite_duration,
    {
        BT_sprites::Sprite::EGG_CRUSHED_4, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_1, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_4, // DIE
    },
    // EGG_PEPPER_2
    pepper_sprite_animation,
    {
        BT_sprites::Sprite::EGG_PEPPER_2, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_1, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_1, // DIE
    },
    // EGG_PEPPER_1
    pepper_sprite_animation,
    {
        BT_sprites::Sprite::EGG_PEPPER_1, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::EGG_PEPPER_2, // PEPPER
        BT_sprites::Sprite::EGG_CRUSHED_1, // DIE
    },
};

Enemy::Enemy(const sf::Vector2f &init_pos, const Sprite_state_machine sprite_state_machine[], std::shared_ptr<Map> map, const AI &ia, const Direction initial_direction)
    : Actor(init_pos, sprite_state_machine[0].sprites[NONE],
            sprite_state_machine[0].sprites[NONE], map),
      sprite_state_machine(sprite_state_machine),
      last_action(NONE),
      acc_delta_t_pepper(0),
      ia(ia),
      initial_direction(initial_direction),
      aStarDirection(Direction::LEFT),
      aStarTile(nullptr),
      initialMovement(true),
      totallyDead(false) {};

void Enemy::pepper()
{
    acc_delta_t_pepper = 0;
    last_action = PEPPER;
}

void Enemy::start_surfing(nod::connection &&ingredient_moving_con, nod::connection &&stop_surfing_con)
{
    ingredient_moving_connection = std::make_unique<nod::connection>(std::move(ingredient_moving_con));
    stop_surfing_connection = std::make_unique<nod::connection>(std::move(stop_surfing_con));
}

void Enemy::stop_surfing()
{
    ingredient_moving_connection->disconnect();
    stop_surfing_connection->disconnect();
    ingredient_moving_connection = nullptr;
    stop_surfing_connection = nullptr;
    die();
}

bool Enemy::isPeppered() const 
{
    return last_action == PEPPER;
}

bool Enemy::isSurfing() const
{
    return ingredient_moving_connection != nullptr;
}

bool Enemy::completelyDead() {
    return totallyDead;
}

void Enemy::move_by_signal(const float y) {
    sprite.setPosition(sprite.getPosition().x, y);
}

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

void Enemy::update(float delta_t) {
    acc_delta_t += delta_t;
    acc_delta_t_pepper += delta_t;

    if (ingredient_moving_connection != nullptr) {
        return;
    }

    new_action = NONE;

    float animation_duration = sprite_state_machine[current_sprite - first_sprite].sprite_duration;

    // DIE
    if (!is_alive()) {
        new_action = DIE;

        if (current_sprite == sprite_state_machine[current_sprite - first_sprite].sprites[new_action]
            && acc_delta_t >= animation_duration) {

            totallyDead = true;
            return;
        }
    }
    // PEPPER
    else if (last_action == PEPPER && acc_delta_t_pepper < pepper_duration) {
        new_action = PEPPER;

        aStarTile = nullptr;
    }
    // A*/MOVE
    else {
        acc_delta_t_pepper = 0;

        float move_x;
        float move_y;

        if (map->outOfMap(*this) && initialMovement) {
            direction = initial_direction;

            move(move_x, move_y, delta_t);
            sprite.move(move_x, move_y);
        }
        else {
            initialMovement = false;

            Direction backup_dir = direction;

            std::vector<std::shared_ptr<Tile>> actorsTiles = map->entityOnTiles(*this);

            const std::shared_ptr<Tile> t = actorsTiles[0];

            bool aStartCalled = false;

            for (auto tile : actorsTiles) {
                if (aStarTile && *tile == *aStarTile) {
                    aStartCalled = true;

                    break;
                }
            }

            if (!aStartCalled && t->isConnector()) {
                direction = ia.getNextMove(t);
                aStarDirection = direction;
                aStarTile = t; 
            }
            else {
                direction = aStarDirection;
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

                    aStarDirection = direction;
                    aStarTile = nullptr;

                    move(move_x, move_y, delta_t);

                    if (map->can_entity_move(move_x, move_y, *this)) {
                        sprite.move(move_x, move_y);
                    }
                    else {
                        fprintf(stderr, "AHORA SI QUE HAY ALGO REALMENTE MAL\n");
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

        BT_sprites::update_sprite(sprite, current_sprite);
    }

    last_action = new_action;
}

const Enemy::Sprite_state_machine *const Enemy::getSpriteStateMachine() const
{
    return sprite_state_machine;
}
