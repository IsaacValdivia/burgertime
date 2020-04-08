#pragma once

#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"
#include "Entity.hpp"

class SpritedEntity : public Entity {
protected:
    BtSprites::Sprite current_sprite;

    sf::Sprite sprite;
public:
    SpritedEntity(const sf::Vector2f &init_pos, BtSprites::Sprite init_sprite);

    sf::FloatRect get_collision_shape() const override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
