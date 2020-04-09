#pragma once

#include "BtSprites.hpp"
#include "Constants.hpp"
#include "SpritedEntity.hpp"

#include <functional>
#include <SFML/Graphics.hpp>

class Bonus : public SpritedEntity {
private:
    static constexpr float respawn_time = 37; // Respawn cooldown of special items
    static constexpr float show_duration = 7; // Spawn time of special items
    static constexpr float giving_points_duration = 1; // Showing time of + points gained

    static constexpr float sprite_scale = 2;

    enum State {
        HIDE,
        SHOW,
        GIVING_POINTS
    };

    const BtSprites::Sprite initial_sprite;

    State state;

    const int points; // Points gained when picking the item

public:
    /**
     * @brief Construct a new Bonus object
     *
     * @param init_pos initial position on map
     * @param init_sprite initial sprite
     * @param points points given if object is grabbed
     */
    Bonus(const sf::Vector2f &init_pos, const BtSprites::Sprite init_sprite,
          const int points);

    /**
     * @brief Called when the player reaches the special item
     *
     */
    void has_been_claimed();

    /**
     * @brief Draws the item if it is not hidden
     *
     * @param target target to draw on
     * @param states states of drawable
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * @brief Checks if it interstects with a certain entity, as long as the item is visible
     *
     * @param entity intersecting entity
     * @return true
     * @return false
     */
    bool intersects_with(const Entity &entity) const override;

    /**
     * @brief Returns number of points obtainable upon grabbing the item
     *
     * @return int points
     */
    int get_points() const;

    /**
     * @brief Main control function
     *
     * @param delta_t delta_t
     */
    void update(const float delta_t) override;
};
