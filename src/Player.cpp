#include "Player.hpp"

#include "Audio.hpp"
#include "InputSystem.hpp"

const Player::SpriteStateMachine Player::sprite_state_machine[] = {
    // PLAYER_DOWNSTAIRS_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BtSprites::Sprite::PLAYER_LEFT_1, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_2, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_STILL_FRONT
    end_game_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BtSprites::Sprite::PLAYER_LEFT_1, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_2, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_DOWNSTAIRS_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BtSprites::Sprite::PLAYER_LEFT_1, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_LEFT_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BtSprites::Sprite::PLAYER_LEFT_2, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_2, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_LEFT_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BtSprites::Sprite::PLAYER_LEFT_3, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_3, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_LEFT_3
    walking_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BtSprites::Sprite::PLAYER_LEFT_1, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_UPSTAIRS_1
    walking_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_BACK, // NONE
        BtSprites::Sprite::PLAYER_LEFT_1, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_2, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_STILL_BACK
    0,
    {
        BtSprites::Sprite::PLAYER_STILL_BACK, // NONE
        BtSprites::Sprite::PLAYER_LEFT_1, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_UPSTAIRS_2
    walking_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_BACK, // NONE
        BtSprites::Sprite::PLAYER_LEFT_1, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_PEPPER_FRONT
    peppering_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BtSprites::Sprite::PLAYER_LEFT_1, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_PEPPER_LEFT
    peppering_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BtSprites::Sprite::PLAYER_LEFT_1, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_PEPPER_BACK
    peppering_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_BACK, // NONE
        BtSprites::Sprite::PLAYER_LEFT_1, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_CELEBRATING, // DROP
        BtSprites::Sprite::PLAYER_CELEBRATING // CELEBRATE
    },
    // PLAYER_CELEBRATING
    end_game_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BtSprites::Sprite::PLAYER_LEFT_1, // LEFT
        BtSprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BtSprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BtSprites::Sprite::PLAYER_PEPPER_LEFT, // PEPPER
        BtSprites::Sprite::PLAYER_DROP_1, // DROP
        BtSprites::Sprite::PLAYER_STILL_FRONT // CELEBRATE
    },
    // PLAYER_DROP_1
    end_game_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_DROP_2, // NONE
        BtSprites::Sprite::PLAYER_DROP_2, // LEFT
        BtSprites::Sprite::PLAYER_DROP_2, // RIGHT
        BtSprites::Sprite::PLAYER_DROP_2, // UP
        BtSprites::Sprite::PLAYER_DROP_2, // DOWN
        BtSprites::Sprite::PLAYER_DROP_2, // PEPPER
        BtSprites::Sprite::PLAYER_DROP_2, // DROP
        BtSprites::Sprite::PLAYER_DROP_2  // CELEBRATE
    },
    // PLAYER_DROP_2
    end_game_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_DROP_3, // NONE
        BtSprites::Sprite::PLAYER_DROP_3, // LEFT
        BtSprites::Sprite::PLAYER_DROP_3, // RIGHT
        BtSprites::Sprite::PLAYER_DROP_3, // UP
        BtSprites::Sprite::PLAYER_DROP_3, // DOWN
        BtSprites::Sprite::PLAYER_DROP_3, // PEPPER
        BtSprites::Sprite::PLAYER_DROP_3, // DROP
        BtSprites::Sprite::PLAYER_DROP_3  // CELEBRATE
    },
    // PLAYER_DROP_3
    end_game_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_DROP_4, // NONE
        BtSprites::Sprite::PLAYER_DROP_4, // LEFT
        BtSprites::Sprite::PLAYER_DROP_4, // RIGHT
        BtSprites::Sprite::PLAYER_DROP_4, // UP
        BtSprites::Sprite::PLAYER_DROP_4, // DOWN
        BtSprites::Sprite::PLAYER_DROP_4, // PEPPER
        BtSprites::Sprite::PLAYER_DROP_4, // DROP
        BtSprites::Sprite::PLAYER_DROP_4  // CELEBRATE
    },
    // PLAYER_DROP_4
    end_game_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_DROP_5, // NONE
        BtSprites::Sprite::PLAYER_DROP_5, // LEFT
        BtSprites::Sprite::PLAYER_DROP_5, // RIGHT
        BtSprites::Sprite::PLAYER_DROP_5, // UP
        BtSprites::Sprite::PLAYER_DROP_5, // DOWN
        BtSprites::Sprite::PLAYER_DROP_5, // PEPPER
        BtSprites::Sprite::PLAYER_DROP_5, // DROP
        BtSprites::Sprite::PLAYER_DROP_5  // CELEBRATE
    },
    // PLAYER_DROP_5
    end_game_sprite_duration,
    {
        BtSprites::Sprite::PLAYER_DROP_4, // NONE
        BtSprites::Sprite::PLAYER_DROP_4, // LEFT
        BtSprites::Sprite::PLAYER_DROP_4, // RIGHT
        BtSprites::Sprite::PLAYER_DROP_4, // UP
        BtSprites::Sprite::PLAYER_DROP_4, // DOWN
        BtSprites::Sprite::PLAYER_DROP_4, // PEPPER
        BtSprites::Sprite::PLAYER_DROP_4, // DROP
        BtSprites::Sprite::PLAYER_DROP_4  // CELEBRATE
    }
};

const BtSprites::Sprite Player::pepper_sprite_state_machine[] = {
    // LEFT
    BtSprites::Sprite::PLAYER_PEPPER_LEFT,
    // RIGHT
    BtSprites::Sprite::PLAYER_PEPPER_LEFT,
    // UP
    BtSprites::Sprite::PLAYER_PEPPER_BACK,
    // DOWN
    BtSprites::Sprite::PLAYER_PEPPER_FRONT,
};

Player::Player(const sf::Vector2f &init_pos, const std::shared_ptr<const Map> map,
               const std::function<void(const sf::Vector2f &, Direction)> &pepper_spawned_func,
               const std::function<bool()> &has_pepper)

    : Actor(init_pos, BtSprites::Sprite::PLAYER_STILL_FRONT,
            BtSprites::Sprite::PLAYER_DOWNSTAIRS_1, map),
      won(false),
      last_action(NONE),
      pepper_spawned_func(pepper_spawned_func),
      has_pepper(has_pepper) {
}

void Player::update(const float delta_t) {
    acc_delta_t += delta_t;

    float animation_duration = sprite_state_machine[
                                current_sprite - first_sprite].sprite_duration;

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

        InputSystem::Input inputToProcess = InputSystem::get_last_input();

        // PEPPER
        if (InputSystem::has_input_just_been_pressed(InputSystem::Input::PEPPER) && has_pepper()) {
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
                 !InputSystem::is_single_input_active(InputSystem::Input::LEFT)) {

            new_action = RIGHT;
            direction = Direction::RIGHT;
            move_x = x_walking_speed * delta_t;
        }
        // LEFT
        else if (inputToProcess == InputSystem::Input::LEFT &&
                 !InputSystem::is_single_input_active(InputSystem::Input::RIGHT)) {

            new_action = LEFT;
            direction = Direction::LEFT;
            move_x = -x_walking_speed * delta_t;
        }
        // UP
        else if (inputToProcess == InputSystem::Input::UP &&
                 !InputSystem::is_single_input_active(InputSystem::Input::DOWN)) {

            new_action = UP;
            direction = Direction::UP;
            move_y = -y_walking_speed * delta_t;
        }
        // DOWN
        else if (inputToProcess == InputSystem::Input::DOWN &&
                 !InputSystem::is_single_input_active(InputSystem::Input::UP)) {

            new_action = DOWN;
            direction = Direction::DOWN;
            move_y = y_walking_speed * delta_t;
        }

        // Want to move.
        if (move_x != 0.0 || move_y != 0.0) {
            // Want to move and can.
            if (map->can_entity_move(move_x, move_y, *this)) {
                sprite.move(move_x, move_y);
                // TODO: comprobar que entity_on_tiles no sea vacio
                player_moved(map->entity_on_tiles(*this)[0]);
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
        if (new_action == PEPPER && has_pepper()) {
            current_sprite = pepper_sprite_state_machine[direction];
        }
        else {
            current_sprite = sprite_state_machine[
                                 current_sprite - first_sprite].sprites[new_action];
        }

        mirror();

        BtSprites::update_sprite(sprite, current_sprite);
    }
    last_action = new_action;
}

bool Player::has_won() const {
    return won;
}

void Player::win() {
    won = true;
}

bool Player::going_x_direction() const {
    return last_action == LEFT || last_action == RIGHT;
}

nod::connection Player::connect_player_moved(
    const std::function<void(const std::shared_ptr<Tile>)> &player_moved_func) {

    return player_moved.connect(player_moved_func);
}
