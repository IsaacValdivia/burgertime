#include "Pepper.hpp"

const BT_sprites::Sprite Pepper::initial_sprite[NUM_TYPES] = {
    BT_sprites::Sprite::PEPPER_BACK_1,
    BT_sprites::Sprite::PEPPER_FRONT_1,
    BT_sprites::Sprite::PEPPER_LEFT_1,
    BT_sprites::Sprite::PEPPER_LEFT_1
};

Pepper::Pepper(const Type _type) : type(_type), acc_delta_t(0) {
    current_sprite = initial_sprite[type];

    BT_sprites::set_initial_sprite(*static_cast<sf::Sprite *>(this), current_sprite);

    this->setScale(sf::Vector2f(sprite_scale, sprite_scale));

    // Set origin in the center of the sprite.
    this->setOrigin({this->getLocalBounds().width / 2,
                     this->getLocalBounds().height / 2});

    if (type == RIGHT) {
        this->scale(-1, 1); // Mirror.
    }

    // TODO: BORRAR
    this->setPosition(200, 200);
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
        return;
    }

    current_sprite = (BT_sprites::Sprite)(current_sprite + 1);

    BT_sprites::update_sprite(*static_cast<sf::Sprite *>(this), current_sprite);

}
