#pragma once

#include "Constants.hpp"
#include "SpritedEntity.hpp"

#include <memory>

class Map;

class Actor : public SpritedEntity {
private:
    static constexpr auto sprite_scale = 2;

protected:
    bool alive; // Is the actor alive?.

    Direction direction; // Current direction.
    Direction mirror_state;

    const std::shared_ptr<const Map> map; // Pointer to map.

    BtSprites::Sprite first_sprite; // Initial sprite.

    /**
     * Flips actor vertically (vertical mirror)
     *
     */
    void mirror();
public:
    /**
     * Constructor for Actor
     *
     * @param init_pos Initial position (x,y)
     * @param init_sprite Initial sprite
     * @param first_sprite First sprite
     * @param map Pointer to map on which it will be generated
     */
    Actor(const sf::Vector2f &init_pos, const BtSprites::Sprite init_sprite,
          const BtSprites::Sprite first_sprite, const std::shared_ptr<const Map> map);

    /**
     * Returns a shape enclosing the Actor, representing its hitbox
     *
     * @return sf::FloatRect
     */
    sf::FloatRect get_collision_shape() const override;

    /**
     * Checks alive field
     *
     * @return bool
     */
    bool is_alive() const;

    /**
     * Sets alive attribute to false
     */
    virtual void die();
};
