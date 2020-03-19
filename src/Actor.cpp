#include "Actor.hpp"

Actor::Actor(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite)
    : alive(true), acc_delta_t(0) {

    BT_sprites::set_initial_sprite(sprite, init_sprite);
    sprite.setScale(sf::Vector2f(actor_scale, actor_scale));

    // Set origin in the center of the sprite.
    sprite.setOrigin({sprite.getLocalBounds().width / 2,
                     sprite.getLocalBounds().height / 2});

    sprite.setPosition(init_pos);
}

bool Actor::is_alive() const {
    return this->alive;
}

void Actor::die() {
    alive = false;
}
