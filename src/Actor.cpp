#include "Actor.hpp"

Actor::Actor(const sf::Vector2f &init_pos, const BT_sprites::Sprite init_sprite, const BT_sprites::Sprite first_sprite)
    : alive(true), Entity(init_pos, init_sprite),
      direction(LEFT),
      first_sprite(first_sprite),
      mirror_state(LEFT) {

    sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));
}

void Actor::mirror() {
    // Mirror sprite.
    if ((mirror_state == Direction::LEFT && direction == Direction::RIGHT) ||
            (mirror_state == Direction::RIGHT && direction != Direction::RIGHT)) {

        if (direction != Direction::RIGHT) {
            mirror_state = Direction::LEFT;
        }
        else {
            mirror_state = Direction::RIGHT;
        }

        sprite.scale(-1, 1); // Mirror.
    }
}

bool Actor::is_alive() const {
    return this->alive;
}

void Actor::die() {
    alive = false;
}
