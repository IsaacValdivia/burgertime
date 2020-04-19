#include "Actor.hpp"

#include "Audio.hpp"
#include "Map.hpp"

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

Actor::Actor(const sf::Vector2f &init_pos, const BtSprites::Sprite init_sprite,
             const BtSprites::Sprite first_sprite, const std::shared_ptr<Map> map)

    : alive(true), SpritedEntity(init_pos, init_sprite),
      direction(LEFT),
      first_sprite(first_sprite),
      mirror_state(LEFT),
      map(map) {

    sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));
}

sf::FloatRect Actor::get_collision_shape() const {
    sf::FloatRect collision_shape = sprite.getGlobalBounds();

    collision_shape.height -= 18;
    collision_shape.top += 18;

    collision_shape.left += 10;
    collision_shape.width -= 20;

    return collision_shape;
}

bool Actor::is_alive() const {
    return this->alive;
}

void Actor::die() {
    alive = false;
}
