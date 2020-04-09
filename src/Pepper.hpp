#pragma once

#include "BtSprites.hpp"
#include "Constants.hpp"
#include "nod.hpp"
#include "SpritedEntity.hpp"

#include <functional>
#include <SFML/Graphics.hpp>

class Pepper : public SpritedEntity {
private:
    static constexpr int NUM_SPRITES_ANIMATION = 4; // Span of the pepper duration

    static constexpr float animation_duration = 0.1;

    static constexpr float sprite_scale = 2;

    static const BtSprites::Sprite initial_sprite[Direction::NUM_DIRECTIONS];

    const Direction type;

    BtSprites::Sprite current_sprite;

    std::function<void()> pepper_finished_func;

public:
    /**
     * @brief Construct a new Pepper object
     *
     * @param init_pos initial pepper position
     * @param type orientation of pepper
     * @param pepper_finished_func callback on finished pepper animation
     */
    Pepper(const sf::Vector2f &init_pos, const Direction type,
           const std::function<void()> &pepper_finished_func);

    /**
     * @brief Main control function
     *
     * @param delta_t delta_t
     */
    void update(const float delta_t) override;
};
