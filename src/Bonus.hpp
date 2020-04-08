#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"
#include "SpritedEntity.hpp"

#include "Constants.hpp"

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
     * @param init_pos
     * @param init_sprite
     * @param points
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
     * @param target
     * @param states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * @brief Checks if it interstects with a certain entity, as long as the item is visible
     *
     * @param entity
     * @return true
     * @return false
     */
    bool intersects_with(const Entity &entity) const override;

    /**
     * @brief Main control function
     *
     * @param delta_t
     */
    void update(float delta_t) override;

    /**
     * @brief Returns number of points obtainable upon grabbing the item
     *
     * @return int
     */
    int get_points() const;
};
