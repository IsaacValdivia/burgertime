#include "Actor.hpp"
#include "Map.hpp"

#include "Audio.hpp"

Actor::Actor(const sf::Vector2f &init_pos, const BT_sprites::Sprite init_sprite, const BT_sprites::Sprite first_sprite, std::shared_ptr<Map> map)
    : alive(true), SpritedEntity(init_pos, init_sprite),
      direction(LEFT),
      first_sprite(first_sprite),
      mirror_state(LEFT),
      map(map)
{
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

sf::FloatRect Actor::getCollisionShape() const {
    sf::FloatRect collisionShape = sprite.getGlobalBounds();

    collisionShape.height -= 18;
    collisionShape.top += 18;

    collisionShape.left += 10;
    collisionShape.width -= 20;
    return collisionShape;
}

bool Actor::is_alive() const {
    return this->alive;
}

void Actor::die() {
    alive = false;
}
