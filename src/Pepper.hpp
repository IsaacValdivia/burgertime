#pragma once

#include "BT_sprites.hpp"

#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"

class Pepper : public sf::Sprite {
public:
    enum Type {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NUM_TYPES
    };
private:
    static constexpr int NUM_SPRITES = 4;

    static constexpr float animation_duration = 2;

    static constexpr float sprite_scale = 2;

    float acc_delta_t;

    static const BT_sprites::Sprite initial_sprite[NUM_TYPES];

    const Type type;

    BT_sprites::Sprite current_sprite;

public:
    Pepper(const Type _type);

    void update(float delta_t); // TODO: Cambiar Actor por otra clase mas generica?
};
