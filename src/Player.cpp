#include "Player.hpp"
#include "InputSystem.hpp"

const BT_sprites::Sprite Player::sprite_state_machine[][NUM_ACTIONS] = {
    // PLAYER_DOWNSTAIRS_1
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
};

Player::Player(const sf::Vector2f &init_pos) 
: Actor(init_pos, BT_sprites::Sprite::PLAYER_STILL_FRONT) {
    current_sprite = BT_sprites::Sprite::PLAYER_STILL_FRONT;
    last_direction = LEFT;
    last_action = NONE;
};

void Player::update(float delta_t) {
    static float t = 0;
    t += delta_t;

    // New action

    Action new_last_direction = last_direction;
    Action new_action = NONE;

    InputSystem::Input inputToProcess = InputSystem::getLastInput();

    if (InputSystem::hasInputJustBeenPressed(InputSystem::Input::PEPPER)) {
        new_action = PEPPER;
        // PEPEREAR
    }
    else if (inputToProcess == InputSystem::Input::RIGHT && !InputSystem::isSingleInputActive(InputSystem::Input::LEFT)) {
        new_action = new_last_direction = RIGHT;
        this->move(velocity * delta_t, 0);
    }
    else if (inputToProcess == InputSystem::Input::LEFT && !InputSystem::isSingleInputActive(InputSystem::Input::RIGHT)) {
        new_action = new_last_direction = LEFT;
        this->move(-velocity * delta_t, 0);
    }
    else if (inputToProcess == InputSystem::Input::UP && !InputSystem::isSingleInputActive(InputSystem::Input::DOWN)) {
        new_action = new_last_direction = UP;
        this->move(0, -velocity / 1.72 * delta_t);
    }
    else if (inputToProcess == InputSystem::Input::DOWN && !InputSystem::isSingleInputActive(InputSystem::Input::UP)) {
        new_action = new_last_direction = DOWN;
        this->move(0, velocity / 1.72 * delta_t);
    }

    // TODO MORIR
    // TODO GANAR

    BT_sprites::Sprite new_sprite = sprite_state_machine[current_sprite][new_action];

    if ((new_sprite != current_sprite && t > 1.5) || last_action != new_action) {
        t = 0;
        // Mirror sprite.
        if ((new_action == RIGHT && last_direction != RIGHT) ||
            ((new_action == LEFT || new_action == DOWN || new_action == UP) 
            && last_direction == RIGHT)) {
            this->scale(-1, 1); // Mirror.
        }

        // Special state machine case.
        if (new_sprite == BT_sprites::Sprite::PLAYER_PEPPER_LEFT
                && last_direction == DOWN) {

            new_sprite = BT_sprites::Sprite::PLAYER_PEPPER_FRONT;
        }

        current_sprite = new_sprite;
        BT_sprites::update_sprite(*static_cast<sf::Sprite *>(this), current_sprite);

        last_direction = new_last_direction;
    }

    last_action = new_action;
}

