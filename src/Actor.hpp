#pragma once

#include "Entity.hpp"
#include "Constants.hpp"

class Actor : public Entity {
private:
    static constexpr auto actor_scale = 2;

protected:
    bool alive;

    Direction last_direction;

    const BT_sprites::Sprite first_bt_sprites_idx;
public:
    Actor(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite, BT_sprites::Sprite first_bt_sprites_idx);

    bool is_alive() const;

    void die();
};
