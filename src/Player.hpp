#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "Actor.hpp"
#include "Map.hpp"
#include "Constants.hpp"

class PlayingStateMachine;

class Player : public Actor {
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

    static constexpr float x_walking_speed = 80;
    static constexpr float y_walking_speed = x_walking_speed / 1.72;

    static constexpr float walking_sprite_duration = 0.1;
    static constexpr float peppering_sprite_duration = 0.2;
    static constexpr float end_game_sprite_duration = 0.2;

    struct Sprite_state_machine_node {
        float sprite_duration;
        BT_sprites::Sprite sprite_state_machine[NUM_ACTIONS];
    };

    static const Sprite_state_machine_node sprite_state_machine[];

    Action last_action;

    Direction last_movement_key;

    std::shared_ptr<Map> map;

    PlayingStateMachine &psm;

    bool won;

public:
    Player(const sf::Vector2f &init_pos, std::shared_ptr<Map> map, PlayingStateMachine &psm);

    void update(float delta_t) override;

    bool has_won() const;

    void win();
};
