#include "Enemy.hpp"

const Enemy::Sprite_state_machine_node Enemy::sausage_sprite_state_machine[] = {
    // SAUSAGE_DOWNSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // NONE
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // LEFT
        BT_sprites::Sprite::SAUSAGE_LEFT_1, // RIGHT
        BT_sprites::Sprite::SAUSAGE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::SAUSAGE_DOWNSTAIRS_1, // DOWN
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
        BT_sprites::Sprite::SAUSAGE_CRUSHED_1, // DIE
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
        BT_sprites::Sprite::SAUSAGE_CRUSHED_2, // DIE
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
        BT_sprites::Sprite::SAUSAGE_CRUSHED_3, // DIE
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

const Enemy::Sprite_state_machine_node Enemy::pickle_sprite_state_machine[] = {
    // PICKLE_DOWNSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // NONE
        BT_sprites::Sprite::PICKLE_LEFT_1, // LEFT
        BT_sprites::Sprite::PICKLE_LEFT_1, // RIGHT
        BT_sprites::Sprite::PICKLE_UPSTAIRS_1, // UP
        BT_sprites::Sprite::PICKLE_DOWNSTAIRS_1, // DOWN
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
        BT_sprites::Sprite::PICKLE_CRUSHED_1, // DIE
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
        BT_sprites::Sprite::PICKLE_CRUSHED_2, // DIE
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
        BT_sprites::Sprite::PICKLE_CRUSHED_3, // DIE
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

const Enemy::Sprite_state_machine_node Enemy::sausage_sprite_state_machine[] = {
    // EGG_DOWNSTAIRS_1
    walking_sprite_duration,
    {
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // NONE
        BT_sprites::Sprite::EGG_LEFT_1, // LEFT
        BT_sprites::Sprite::EGG_LEFT_1, // RIGHT
        BT_sprites::Sprite::EGG_UPSTAIRS_1, // UP
        BT_sprites::Sprite::EGG_DOWNSTAIRS_1, // DOWN
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
        BT_sprites::Sprite::EGG_CRUSHED_1, // DIE
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
        BT_sprites::Sprite::EGG_CRUSHED_2, // DIE
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
        BT_sprites::Sprite::EGG_CRUSHED_3, // DIE
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

Enemy::Enemy(const sf::Vector2f &init_pos, const Sprite_state_machine_node sprite_state_machine[])
    : Actor(init_pos, sprite_state_machine[0].sprite_state_machine[NONE],
            sprite_state_machine[0].sprite_state_machine[NONE]),
      sprite_state_machine(sprite_state_machine), acc_delta_t_pepper(0) {

    last_action = NONE;
};

void Enemy::update(float delta_t) {
    acc_delta_t += delta_t;
    acc_delta_t_pepper += delta_t;

    float animation_duration = sprite_state_machine[current_sprite - first_bt_sprites_idx].sprite_duration;

    // Get new action

    Direction new_last_direction = last_direction;
    Action new_action = NONE;

    bool update_sprite = true;

    // DIE
    if (!is_alive()) {
        new_action = DIE;
    }
    // PEPPER
    else if (last_action == PEPPER && acc_delta_t_pepper < pepper_duration) {
        new_action = PEPPER;
    }
    // A*
    else {
        acc_delta_t_pepper = 0;

        // A* TODO
    }

    // Set new sprite.
    BT_sprites::Sprite new_sprite = update_sprite ?
                                    sprite_state_machine[current_sprite - first_bt_sprites_idx].sprite_state_machine[new_action]
                                    :
                                    current_sprite;

    if (new_sprite != current_sprite &&
            (acc_delta_t > animation_duration || new_action != last_action)) {

        // Reset accumulated delta.
        acc_delta_t = 0;

        // Mirror sprite.
        if ((new_action == RIGHT && last_direction != Direction::RIGHT) ||
                ((new_action == LEFT || new_action == DOWN || new_action == UP)
                 && last_direction == Direction::RIGHT)) {

            sprite.scale(-1, 1); // Mirror.
        }

        current_sprite = new_sprite;
        BT_sprites::update_sprite(sprite, current_sprite);
    }

    last_direction = new_last_direction;
    last_action = new_action;
}
