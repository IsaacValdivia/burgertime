#pragma once

#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"
#include "Entity.hpp"

class SpritedEntity : public Entity {
protected:
    BT_sprites::Sprite current_sprite;

    sf::Sprite sprite;
public:
    SpritedEntity(const sf::Vector2f &init_pos, BT_sprites::Sprite init_sprite);

    sf::FloatRect getCollisionShape() const override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
