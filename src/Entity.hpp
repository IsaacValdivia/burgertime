#pragma once

#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"

class Entity : public sf::Drawable {
protected:
    float acc_delta_t;

    BT_sprites::Sprite current_sprite;

    sf::Sprite sprite;

public:
    Entity(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite);

    virtual void update(float delta_t) = 0;
};
