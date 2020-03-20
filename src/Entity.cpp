#include "Entity.hpp"

Entity::Entity(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite)
    : acc_delta_t(0), current_sprite(init_sprite) {

    BT_sprites::set_initial_sprite(sprite, init_sprite);

    // Set origin in the center of the sprite.
    sprite.setOrigin({sprite.getLocalBounds().width / 2,
                      sprite.getLocalBounds().height / 2});

    sprite.setPosition(init_pos);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

