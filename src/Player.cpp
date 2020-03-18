#include "Player.hpp"
#include "InputSystem.hpp"

const Player::Sprite_state_machine_node Player::sprite_state_machine[] = {
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
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
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
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
    },
    // PLAYER_DOWNSTAIRS_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_FRONT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
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
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
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
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
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
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
    },
    // PLAYER_UPSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_BACK, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_2, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_BACK, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
    },
    // PLAYER_STILL_BACK
    0,
    {
        BT_sprites::Sprite::PLAYER_STILL_BACK, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_BACK, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
    },
    // PLAYER_UPSTAIRS_2
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_BACK, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_BACK, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
    },
    // PLAYER_PEPPER_FRONT
    peppering_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_FRONT, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_FRONT, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
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
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
    },
    // PLAYER_PEPPER_BACK
    peppering_sprite_duration,
    {
        BT_sprites::Sprite::PLAYER_STILL_BACK, // NONE
        BT_sprites::Sprite::PLAYER_LEFT_1, // LEFT
        BT_sprites::Sprite::PLAYER_LEFT_1, // RIGHT
        BT_sprites::Sprite::PLAYER_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PLAYER_DOWNSTAIRS_1, // DOWN
        BT_sprites::Sprite::PLAYER_PEPPER_BACK, // PEPPER
        BT_sprites::Sprite::PLAYER_CELEBRATING, // DROP
        BT_sprites::Sprite::PLAYER_CELEBRATING  // CELEBRATE
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
        BT_sprites::Sprite::PLAYER_STILL_FRONT  // CELEBRATE
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

Player::Player(const sf::Vector2f &init_pos, std::shared_ptr<MapView> mapView)
    : Actor(init_pos, BT_sprites::Sprite::PLAYER_STILL_FRONT), mapView(mapView), won(false) {

    current_sprite = BT_sprites::Sprite::PLAYER_STILL_FRONT;

    last_direction = LEFT;
    last_action = NONE;
};

bool Player::has_won() {
    return won;
}

void Player::win() {
    won = true;
}

void Player::update(float delta_t) {
    acc_delta_t += delta_t;

    float animation_duration = sprite_state_machine[current_sprite].sprite_duration;

    // Get new action

    Action new_last_direction = last_direction;
    Action new_action = NONE;

    bool update_sprite = true;

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
        // If Peter is peppering he can not move.
        if (last_action == PEPPER && acc_delta_t < animation_duration) {
            return;
        }

        float move_x = 0;
        float move_y = 0;

        InputSystem::Input inputToProcess = InputSystem::getLastInput();

        // PEPPER
        if (InputSystem::hasInputJustBeenPressed(InputSystem::Input::PEPPER)) {
            new_action = PEPPER;
            // PEPEREAR
        }
        // RIGHT
        else if (inputToProcess == InputSystem::Input::RIGHT &&
                 !InputSystem::isSingleInputActive(InputSystem::Input::LEFT)) {

            new_action = new_last_direction = RIGHT;
            move_x = x_walking_speed * delta_t;
        }
        // LEFT
        else if (inputToProcess == InputSystem::Input::LEFT &&
                 !InputSystem::isSingleInputActive(InputSystem::Input::RIGHT)) {

            new_action = new_last_direction = LEFT;
            move_x = -x_walking_speed * delta_t;
        }
        // UP
        else if (inputToProcess == InputSystem::Input::UP &&
                 !InputSystem::isSingleInputActive(InputSystem::Input::DOWN)) {

            new_action = new_last_direction = UP;
            move_y = -y_walking_speed * delta_t;
        }
        // DOWN
        else if (inputToProcess == InputSystem::Input::DOWN &&
                 !InputSystem::isSingleInputActive(InputSystem::Input::UP)) {

            new_action = new_last_direction = DOWN;
            move_y = y_walking_speed * delta_t;
        }

        // Want to move.
        if (move_x != 0.0 || move_y != 0.0) {
            // Want to move and can.
            if (mapView->player_can_move(move_x, move_y, *static_cast<sf::Sprite *>(this))) {
                this->move(move_x, move_y);
            }
            // Want to move but can't.
            else {
                new_last_direction = last_direction;
                new_action = last_action;

                update_sprite = false;
            }
        }
    }

    // Set new sprite.
    BT_sprites::Sprite new_sprite = update_sprite ?
                                    sprite_state_machine[current_sprite].sprite_state_machine[new_action]
                                    :
                                    current_sprite;

    if (new_sprite != current_sprite &&
            (acc_delta_t > animation_duration || new_action != last_action)) {

        // Reset accumulated delta.
        acc_delta_t = 0;

        // Mirror sprite.
        if ((new_action == RIGHT && last_direction != RIGHT) ||
                ((new_action == LEFT || new_action == DOWN || new_action == UP)
                 && last_direction == RIGHT)) {

            this->scale(-1, 1); // Mirror.
        }

        // Special state machine case (PEPPER_FRONT).
        if (new_sprite == BT_sprites::Sprite::PLAYER_PEPPER_LEFT
                && last_direction == DOWN) {

            new_sprite = BT_sprites::Sprite::PLAYER_PEPPER_FRONT;
        }

        current_sprite = new_sprite;
        BT_sprites::update_sprite(*static_cast<sf::Sprite *>(this), current_sprite);
    }

    last_direction = new_last_direction;
    last_action = new_action;
}
