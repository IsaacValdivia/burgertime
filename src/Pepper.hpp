#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"
#include "nod.hpp"
#include "Entity.hpp"

#include "Constants.hpp"


class Pepper : public Entity {
private:
    static constexpr int NUM_SPRITES_ANIMATION = 4;

    static constexpr float animation_duration = 0.1;

    static constexpr float sprite_scale = 2;

    static const BT_sprites::Sprite initial_sprite[Direction::NUM_DIRECTIONS];

    const Direction type;

    BT_sprites::Sprite current_sprite;

    nod::unsafe_signal<void()> pepper_finished;

public:
    Pepper(const sf::Vector2f &init_pos, const Direction type, const std::function<void()> &pepper_finished_func);

    void update(float delta_t) override;
};
