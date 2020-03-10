#include "Player.hpp"

const BT_sprites::Sprite Player::sprite_state_machine[][NUM_PLAYER_ACTIONS] = {
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

Player::Player() {
    current_sprite = BT_sprites::Sprite::PLAYER_STILL_FRONT;
    last_direction = NONE;

    BT_sprites::set_initial_sprite(player_sprite, BT_sprites::Sprite::PLAYER_STILL_FRONT);
    player_sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));

    // Set origin in the center of the sprite.
    player_sprite.setOrigin({player_sprite.getLocalBounds().width / 2,
                             player_sprite.getLocalBounds().height / 2});

    // TODO: BORRAR
    player_sprite.setPosition(80, 80);
};

void Player::update(Action pa) {
    BT_sprites::Sprite new_sprite = sprite_state_machine[current_sprite][pa];

    // Set new sprite.
    if (new_sprite != current_sprite) {
        // Mirror sprite.
        if ((pa == RIGHT && last_direction != RIGHT) ||
                ((pa == LEFT || pa == DOWN || pa == UP) && last_direction == RIGHT)) {
            player_sprite.scale(-1, 1); // Mirror.
        }

        // Special state machine case.
        if (new_sprite == BT_sprites::Sprite::PLAYER_PEPPER_LEFT
                && last_direction == DOWN) {

            new_sprite = BT_sprites::Sprite::PLAYER_PEPPER_FRONT;
        }

        current_sprite = new_sprite;
        BT_sprites::update_sprite(player_sprite, current_sprite);
    }

    // Move
    switch (pa) {
        case LEFT:
            last_direction = LEFT;
            player_sprite.move(-step_size, 0);
            break;
        case RIGHT:
            last_direction = RIGHT;
            player_sprite.move(step_size, 0);
            break;
        case UP:
            last_direction = UP;
            player_sprite.move(0, -step_size);
            break;
        case DOWN:
            last_direction = DOWN;
            player_sprite.move(0, step_size);
            break;
        default:
            break;
    }
}

sf::Sprite Player::get_sprite() const {
    return player_sprite;
}
