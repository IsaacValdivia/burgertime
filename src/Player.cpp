#include "Player.hpp"
#include "InputSystem.hpp"

const Player::Sprite_state_machine Player::sprite_state_machine[] = {
    // PLAYER_DOWNSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_2, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_STILL_FRONT
    end_game_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_2, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_DOWNSTAIRS_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_LEFT_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_2, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_2, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_LEFT_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_3, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_3, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_LEFT_3
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_UPSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_BACK, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_2, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_STILL_BACK
    0,
    {
        BT_sprites::Sprite::PLAYER_STILL_BACK, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_UPSTAIRS_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_BACK, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_PEPPER_FRONT
    peppering_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_PEPPER_LEFT
    peppering_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_PEPPER_BACK
    peppering_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_BACK, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_CELEBRATING
    end_game_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BT_sprites::Sprite::PLAYER_DROP_1, // DROP
        BT_sprites::Sprite::PLAYER_STILL_FRONT // CELEBRATE
    },
    // PLAYER_DROP_1
    end_game_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_DROP_2, // NONE
        BT_sprites::Sprite::PLAYER_DROP_2, // LEFT
        BT_sprites::Sprite::PLAYER_DROP_2, // RIGHT
        BT_sprites::Sprite::PLAYER_DROP_2, // UP
        BT_sprites::Sprite::PLAYER_DROP_2, // DOWN
        BT_sprites::Sprite::PLAYER_DROP_2, // PEPPER
        BT_sprites::Sprite::PLAYER_DROP_2, // DROP
        BT_sprites::Sprite::PLAYER_DROP_2  // CELEBRATE
    },
    // PLAYER_DROP_2
    end_game_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_DROP_3, // NONE
        BT_sprites::Sprite::PLAYER_DROP_3, // LEFT
        BT_sprites::Sprite::PLAYER_DROP_3, // RIGHT
        BT_sprites::Sprite::PLAYER_DROP_3, // UP
        BT_sprites::Sprite::PLAYER_DROP_3, // DOWN
        BT_sprites::Sprite::PLAYER_DROP_3, // PEPPER
        BT_sprites::Sprite::PLAYER_DROP_3, // DROP
        BT_sprites::Sprite::PLAYER_DROP_3  // CELEBRATE
    },
    // PLAYER_DROP_3
    end_game_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_DROP_4, // NONE
        BT_sprites::Sprite::PLAYER_DROP_4, // LEFT
        BT_sprites::Sprite::PLAYER_DROP_4, // RIGHT
        BT_sprites::Sprite::PLAYER_DROP_4, // UP
        BT_sprites::Sprite::PLAYER_DROP_4, // DOWN
        BT_sprites::Sprite::PLAYER_DROP_4, // PEPPER
        BT_sprites::Sprite::PLAYER_DROP_4, // DROP
        BT_sprites::Sprite::PLAYER_DROP_4  // CELEBRATE
    },
    // PLAYER_DROP_4
    end_game_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_DROP_5, // NONE
        BT_sprites::Sprite::PLAYER_DROP_5, // LEFT
        BT_sprites::Sprite::PLAYER_DROP_5, // RIGHT
        BT_sprites::Sprite::PLAYER_DROP_5, // UP
        BT_sprites::Sprite::PLAYER_DROP_5, // DOWN
        BT_sprites::Sprite::PLAYER_DROP_5, // PEPPER
        BT_sprites::Sprite::PLAYER_DROP_5, // DROP
        BT_sprites::Sprite::PLAYER_DROP_5  // CELEBRATE
    },
    // PLAYER_DROP_5
    end_game_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_DROP_4, // NONE
        BT_sprites::Sprite::PLAYER_DROP_4, // LEFT
        BT_sprites::Sprite::PLAYER_DROP_4, // RIGHT
        BT_sprites::Sprite::PLAYER_DROP_4, // UP
        BT_sprites::Sprite::PLAYER_DROP_4, // DOWN
        BT_sprites::Sprite::PLAYER_DROP_4, // PEPPER
        BT_sprites::Sprite::PLAYER_DROP_4, // DROP
        BT_sprites::Sprite::PLAYER_DROP_4  // CELEBRATE
    }
};

const BT_sprites::Sprite Player::pepper_sprite_state_machine[] = {
    // LEFT
    BT_sprites::Sprite::PLAYER_PEPPER_LEFT,
    // RIGHT
    BT_sprites::Sprite::PLAYER_PEPPER_LEFT,
    // UP
    BT_sprites::Sprite::PLAYER_PEPPER_BACK,
    // DOWN
    BT_sprites::Sprite::PLAYER_PEPPER_FRONT,
};

Player::Player(const sf::Vector2f &init_pos, std::shared_ptr<Map> map, const std::function<void(const sf::Vector2f&, Direction)> &pepper_spawned_func)
    : Actor(init_pos, BT_sprites::Sprite::PLAYER_STILL_FRONT, BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, map),
      won(false),
      last_action(NONE),
      pepper_spawned_func(pepper_spawned_func)
{
}

bool Player::has_won() const {
    return won;
}

void Player::win() {
    won = true;
}

void Player::update(float delta_t) {
    acc_delta_t += delta_t;

    float animation_duration = sprite_state_machine[current_sprite - first_sprite].sprite_duration;

    if (last_action == PEPPER && acc_delta_t < animation_duration) {
        return;
    }

    // Get new action and direction.

    new_action = NONE;

    // WIN
    if (has_won()) {
        new_action = CELEBRATE;
    }
    // LOSE
    else if (!is_alive()) {
        new_action = DROP;
    }
    // MOVEMENT/PEPPER
    else {

        float move_x = 0;
        float move_y = 0;

        InputSystem::Input inputToProcess = InputSystem::getLastInput();

        // PEPPER
        if (InputSystem::hasInputJustBeenPressed(InputSystem::Input::PEPPER)) {
            new_action = PEPPER;

            sf::Vector2f pepper_pos(sprite.getPosition().x, sprite.getPosition().y);

            switch (direction) {
                case Direction::LEFT:
                    pepper_pos.x -= sprite.getGlobalBounds().width;
                    break;
                case Direction::RIGHT:
                    pepper_pos.x += sprite.getGlobalBounds().width;
                    break;
                case Direction::UP:
                    pepper_pos.y -= sprite.getGlobalBounds().height;
                    break;
                case Direction::DOWN:
                    pepper_pos.y += sprite.getGlobalBounds().height;
                    break;
                default:
                    break;
            }

            pepper_spawned_func(sf::Vector2f(pepper_pos.x, pepper_pos.y), direction);
        }
        // RIGHT
        else if (inputToProcess == InputSystem::Input::RIGHT &&
                 !InputSystem::isSingleInputActive(InputSystem::Input::LEFT)) {

            new_action = RIGHT;
            direction = Direction::RIGHT;
            move_x = x_walking_speed * delta_t;
        }
        // LEFT
        else if (inputToProcess == InputSystem::Input::LEFT &&
                 !InputSystem::isSingleInputActive(InputSystem::Input::RIGHT)) {

            new_action = LEFT;
            direction = Direction::LEFT;
            move_x = -x_walking_speed * delta_t;
        }
        // UP
        else if (inputToProcess == InputSystem::Input::UP &&
                 !InputSystem::isSingleInputActive(InputSystem::Input::DOWN)) {

            new_action = UP;
            direction = Direction::UP;
            move_y = -y_walking_speed * delta_t;
        }
        // DOWN
        else if (inputToProcess == InputSystem::Input::DOWN &&
                 !InputSystem::isSingleInputActive(InputSystem::Input::UP)) {

            new_action = DOWN;
            direction = Direction::DOWN;
            move_y = y_walking_speed * delta_t;
        }

        // Want to move.
        if (move_x != 0.0 || move_y != 0.0) {
            // Want to move and can.
            if (map->can_actor_move(move_x, move_y, *this)) {
                sprite.move(move_x, move_y);
                player_moved(*map->actorOnTiles(*this)[0]);
            }
            // Want to move but can't.
            else {
                new_action = last_action;

                return;
            }
        }
    }

    // New sprite.

    if (acc_delta_t > animation_duration || new_action != last_action) {
        acc_delta_t = 0;

        // Special case.
        if (new_action == PEPPER) {
            current_sprite = pepper_sprite_state_machine[direction];
        }
        else {
            current_sprite = sprite_state_machine[current_sprite - first_sprite].sprites[new_action];
        }

        mirror();

        BT_sprites::update_sprite(sprite, current_sprite);
    }
    last_action = new_action;
}

void Player::connect_player_moved(const std::function<void(const Tile&)> &player_moved_func)
{
    player_moved.connect(player_moved_func);
}
