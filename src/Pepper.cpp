#include "Pepper.hpp"

const BtSprites::Sprite Pepper::initial_sprite[Direction::NUM_DIRECTIONS] = {
    BtSprites::Sprite::PEPPER_LEFT_1,
    BtSprites::Sprite::PEPPER_LEFT_1,
    BtSprites::Sprite::PEPPER_BACK_1,
    BtSprites::Sprite::PEPPER_FRONT_1,
};

Pepper::Pepper(const sf::Vector2f &init_pos, const Direction type,
               const std::function<void()> &pepper_finished_func)

    : SpritedEntity(init_pos, initial_sprite[type]),
      type(type),
      current_sprite(initial_sprite[type]),
      pepper_finished_func(pepper_finished_func) {

    sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));

    if (type == Direction::RIGHT) {
        sprite.scale(-1, 1); // Mirror.
    }
};

void Pepper::update(const float delta_t) {
    acc_delta_t += delta_t;

    if (acc_delta_t < animation_duration) {
        return;
    }

    acc_delta_t = 0;

    // Delete pepper.
    if (current_sprite == initial_sprite[type] + NUM_SPRITES_ANIMATION - 1) {
        pepper_finished_func();
        return;
    }

    current_sprite = (BtSprites::Sprite)(current_sprite + 1);

    BtSprites::update_sprite(sprite, current_sprite);
}
