#pragma once

#include "BT_sprites.hpp"

#include "Entity.hpp"

#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"
#include "Constants.hpp"

class PlayingStateMachine;

class Pepper : public Entity {
private:
    static constexpr int NUM_SPRITES_ANIMATION = 4;

    static constexpr float animation_duration = 0.1;

    static constexpr float sprite_scale = 2;

    static const BT_sprites::Sprite initial_sprite[Direction::NUM_DIRECTIONS];

    const Direction type;

    PlayingStateMachine &psm;

    BT_sprites::Sprite current_sprite;

public:
    Pepper(const sf::Vector2f &init_pos, const Direction type, PlayingStateMachine &psm);

    void update(float delta_t) override;
};
