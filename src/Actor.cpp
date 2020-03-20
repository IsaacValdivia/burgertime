#include "Actor.hpp"

Actor::Actor(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite)
    : alive(true), Entity(init_pos, init_sprite) {

    sprite.setScale(sf::Vector2f(actor_scale, actor_scale));
}

bool Actor::is_alive() const {
    return this->alive;
}

void Actor::die() {
    alive = false;
}
