#include "SpritedEntity.hpp"

SpritedEntity::SpritedEntity(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite)
    : Entity(), current_sprite(init_sprite) {

    BT_sprites::set_initial_sprite(sprite, init_sprite);

    // Set origin in the center of the sprite.
    sprite.setOrigin({sprite.getLocalBounds().width / 2,
                      sprite.getLocalBounds().height / 2});

    sprite.setPosition(init_pos);
}

sf::FloatRect SpritedEntity::getCollisionShape() const {
    sf::FloatRect collisionShape = sprite.getGlobalBounds();

    return collisionShape;
}

void SpritedEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);

#if false
    auto collisionShape = getCollisionShape();
    sf::RectangleShape drawShape;
    drawShape.setOutlineColor(sf::Color::Red);
    drawShape.setFillColor(sf::Color::Transparent);
    drawShape.setOutlineThickness(0.8);
    drawShape.setPosition(collisionShape.left, collisionShape.top);
    drawShape.setSize(sf::Vector2f(collisionShape.width, collisionShape.height));
    target.draw(drawShape, states);
#endif
}
