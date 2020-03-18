#include "Actor.hpp"

Actor::Actor(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite)
    : alive(true), acc_delta_t(0) {

    BT_sprites::set_initial_sprite(*static_cast<sf::Sprite *>(this), init_sprite);
    this->setScale(sf::Vector2f(actor_scale, actor_scale));

    // Set origin in the center of the sprite.
    this->setOrigin({this->getLocalBounds().width / 2,
                     this->getLocalBounds().height / 2});

    this->setPosition(init_pos);
}

bool Actor::is_alive() {
    return this->alive;
}

void Actor::die() {
    alive = false;
}
