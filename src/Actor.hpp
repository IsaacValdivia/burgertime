#pragma once

#include "SpritedEntity.hpp"
#include "Constants.hpp"

#include <memory>

class Map;

class Actor : public SpritedEntity {
private:
    static constexpr auto sprite_scale = 2;

protected:
    bool alive; // Is the actor alive?.

    Direction direction; // Current direction.
    Direction mirror_state;

    std::shared_ptr<Map> map; // Pointer to map.

    const BT_sprites::Sprite first_sprite; // Initial sprite.

    void mirror();
public:
    /**
     * [description]
     * 
     * @param init_pos 
     * @param init_sprite 
     * @param first_sprite 
     * @param map 
     */
    Actor(const sf::Vector2f &init_pos, const BT_sprites::Sprite init_sprite, const BT_sprites::Sprite first_sprite, std::shared_ptr<Map> map);

    /**
     * Returns a e
     * 
     * @return sf::FloatRect 
     */
    sf::FloatRect getCollisionShape() const override;

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
