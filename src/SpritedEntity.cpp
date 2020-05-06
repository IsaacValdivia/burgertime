#include "SpritedEntity.hpp"

SpritedEntity::SpritedEntity(const sf::Vector2f &init_pos,
                             const BtSprites::Sprite init_sprite)

    : Entity(), current_sprite(init_sprite) {

    BtSprites::set_initial_sprite(sprite, init_sprite);

    // Set origin in the center of the sprite.
    sprite.setOrigin({sprite.getLocalBounds().width / 2,
                      sprite.getLocalBounds().height / 2});

    sprite.setPosition(init_pos);
}

sf::FloatRect SpritedEntity::get_collision_shape() const {
    sf::FloatRect collision_shape = sprite.getGlobalBounds();

    return collision_shape;
}

void SpritedEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);

#if false
    auto collision_shape = get_collision_shape();
    sf::RectangleShape drawShape;
    drawShape.setOutlineColor(sf::Color::Red);
    drawShape.setFillColor(sf::Color::Transparent);
    drawShape.setOutlineThickness(0.8);
    drawShape.setPosition(collision_shape.left, collision_shape.top);
    drawShape.setSize(sf::Vector2f(collision_shape.width, collision_shape.height));
    target.draw(drawShape, states);
#endif
}
