#pragma once

#include "Entity.hpp"
#include "Constants.hpp"

class Actor : public Entity {
private:
    static constexpr auto sprite_scale = 2;

protected:
    bool alive;

    Direction direction;
    Direction mirror_state;

    const BT_sprites::Sprite first_sprite;

    void mirror();
public:
    Actor(const sf::Vector2f &init_pos, const BT_sprites::Sprite init_sprite, const BT_sprites::Sprite first_sprite);

    bool is_alive() const;

    void die();
};
