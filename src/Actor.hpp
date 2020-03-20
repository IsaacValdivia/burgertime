#pragma once

#include "Entity.hpp"

class Actor : public Entity {
private:
    static constexpr auto actor_scale = 2;

protected:
    bool alive;

public:
    Actor(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite);

    bool is_alive() const;

    void die();
};
