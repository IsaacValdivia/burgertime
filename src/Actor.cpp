#include "Actor.hpp"

Actor::Actor(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite, BT_sprites::Sprite first_bt_sprites_idx)
    : alive(true), Entity(init_pos, init_sprite), last_direction(LEFT),
      first_bt_sprites_idx(first_bt_sprites_idx) {

    sprite.setScale(sf::Vector2f(actor_scale, actor_scale));
}

bool Actor::is_alive() const {
    return this->alive;
}

void Actor::die() {
    alive = false;
}
