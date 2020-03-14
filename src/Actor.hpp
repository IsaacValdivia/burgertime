#pragma once

#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"

class Actor : public sf::Sprite
{
private:
    static constexpr auto actor_scale = 2;

protected:
    static constexpr auto velocity = 4;

    float acc_delta_t;

    bool alive;

    BT_sprites::Sprite current_sprite;

public:
    Actor(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite);

    bool is_alive();

    virtual void update(float delta_t) = 0;
};
