#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"
#include "nod.hpp"
#include "SpritedEntity.hpp"

#include "Constants.hpp"

class Pepper : public SpritedEntity {
private:
    static constexpr int NUM_SPRITES_ANIMATION = 4;

    static constexpr float animation_duration = 0.1;

    static constexpr float sprite_scale = 2;

    static const BtSprites::Sprite initial_sprite[Direction::NUM_DIRECTIONS];

    const Direction type;

    BtSprites::Sprite current_sprite;

    std::function<void()> pepper_finished_func;

public:
    Pepper(const sf::Vector2f &init_pos, const Direction type,
           const std::function<void()> &pepper_finished_func);

    void update(const float delta_t) override;
};
