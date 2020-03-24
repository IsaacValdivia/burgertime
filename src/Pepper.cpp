#include "Pepper.hpp"

const BT_sprites::Sprite Pepper::initial_sprite[Direction::NUM_DIRECTIONS] = {
    BT_sprites::Sprite::PEPPER_LEFT_1,
    BT_sprites::Sprite::PEPPER_LEFT_1,
    BT_sprites::Sprite::PEPPER_BACK_1,
    BT_sprites::Sprite::PEPPER_FRONT_1,
};

Pepper::Pepper(const sf::Vector2f &init_pos, const Direction type, const std::function<void()> &pepper_finished_func)
    : Entity(init_pos, initial_sprite[type]),
      type(type),
      current_sprite(initial_sprite[type]) {
    
    pepper_finished.connect(pepper_finished_func);

    sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));

    if (type == Direction::RIGHT) {
        sprite.scale(-1, 1); // Mirror.
    }
};

void Pepper::update(float delta_t) {
    acc_delta_t += delta_t;

    if (acc_delta_t < animation_duration) {
        return;
    }

    acc_delta_t = 0;

    // Delete pepper.
    if (current_sprite == initial_sprite[type] + NUM_SPRITES_ANIMATION - 1) {
        pepper_finished();
        return;
    }

    current_sprite = (BT_sprites::Sprite)(current_sprite + 1);

    BT_sprites::update_sprite(sprite, current_sprite);
}
