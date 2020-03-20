#include "Pepper.hpp"
#include "PlayingStateMachine.hpp"

const BT_sprites::Sprite Pepper::initial_sprite[Direction::NUM_DIRECTIONS] = {
    BT_sprites::Sprite::PEPPER_LEFT_1,
    BT_sprites::Sprite::PEPPER_LEFT_1,
    BT_sprites::Sprite::PEPPER_BACK_1,
    BT_sprites::Sprite::PEPPER_FRONT_1,
};

Pepper::Pepper(const sf::Vector2f &init_pos, const Direction type, PlayingStateMachine &psm)
    : Entity(init_pos, initial_sprite[type]), type(type), psm(psm) {
    current_sprite = initial_sprite[type];

    sprite.setScale(sf::Vector2f(scale, scale));

    if (type == Direction::RIGHT) {
        sprite.scale(-1, 1); // Mirror.
    }
};

void Pepper::update(float delta_t) {
    acc_delta_t += delta_t;

    if (acc_delta_t < animation_duration) {
        return;
    }

    // Reset accumulated delta.
    acc_delta_t = 0;

    // BORRAR CUANDO TERMINADO para evaitar esto.

    if (current_sprite == initial_sprite[type] + NUM_SPRITES - 1) {
        psm.deletePepper();
        return;
    }

    current_sprite = (BT_sprites::Sprite)(current_sprite + 1);

    BT_sprites::update_sprite(sprite, current_sprite);

}
