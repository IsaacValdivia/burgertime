#pragma once

#include "BtSprites.hpp"
#include "Entity.hpp"

#include <SFML/Graphics.hpp>

class SpritedEntity : public Entity {
protected:
    BtSprites::Sprite current_sprite;

    sf::Sprite sprite;
public:
    /**
     * @brief Construct a new Sprited Entity object
     *
     * @param init_pos initial sprited entitiy position
     * @param init_sprite initial sprited entity sprite
     */
    SpritedEntity(const sf::Vector2f &init_pos, const BtSprites::Sprite init_sprite);

    /**
     * @brief Returns a hitbox around the sprited entity
     *
     * @return sf::FloatRect collision shape around the entity
     */
    sf::FloatRect get_collision_shape() const override;

    /**
     * @brief Draw the object on screen
     *
     * @param target target to draw on
     * @param states states of drawable
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
