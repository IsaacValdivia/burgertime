#pragma once

#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"

class Actor : public sf::Sprite {
private:
    static constexpr auto actor_scale = 2;

protected:
    static constexpr float x_walking_speed = 80;
    static constexpr float y_walking_speed = x_walking_speed / 1.72;

    static constexpr float walking_sprite_duration = 0.1;

    float acc_delta_t;

    bool alive;

    BT_sprites::Sprite current_sprite;

public:
    Actor(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite);

    bool is_alive();

    void die();

    virtual void update(float delta_t) = 0;
};
