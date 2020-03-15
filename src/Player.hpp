#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "BT_sprites.hpp"

#include "Actor.hpp"
#include "MapView.hpp"

// TODO: REPETIR CUANDO HAYA ALGO DECIDIDO?

class Player : public Actor
{
private:
    enum Action {
        NONE,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        PEPPER,
        DROP,
        CELEBRATE,
        NUM_ACTIONS
    };

    struct Sprite_state_machine_node {
        float sprite_duration;
        BT_sprites::Sprite sprite_state_machine[NUM_ACTIONS];
    };

    static constexpr float peppering_sprite_duration = 0.2;

    static constexpr float end_game_sprite_duration = 0.2;

    static const Sprite_state_machine_node sprite_state_machine[];

    Action last_direction; // LEFT, RIGHT, UP or DOWN only.

    Action last_action;

    std::shared_ptr<MapView> mapView;

    bool won;

public:
    Player(const sf::Vector2f &init_pos, std::shared_ptr<MapView> mapview);

    void update(float delta_t) override;

    bool has_won();

    void win();
};
