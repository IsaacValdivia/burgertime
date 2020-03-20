#pragma once

#include <SFML/Graphics.hpp>

#include "Actor.hpp"

class Enemy : public Actor {
public:
    enum Action {
        NONE,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        PEPPER,
        DIE,
        NUM_ACTIONS
    };

    struct Sprite_state_machine_node {
        float sprite_duration;
        BT_sprites::Sprite sprite_state_machine[NUM_ACTIONS];
    };

    static const Sprite_state_machine_node sausage_sprite_state_machine[];
    static const Sprite_state_machine_node egg_sprite_state_machine[];
    static const Sprite_state_machine_node pickle_sprite_state_machine[];

private:
    static constexpr float x_walking_speed = 80;
    static constexpr float y_walking_speed = x_walking_speed / 1.72;

    static constexpr float walking_sprite_duration = 0.1;
    static constexpr float dying_sprite_duration = 0.1;
    static constexpr float pepper_sprite_animation = 0.2;

    static constexpr float pepper_duration = 2;

    const Sprite_state_machine_node *const sprite_state_machine;

    Action last_action;

    float acc_delta_t_pepper;

public:
    Enemy(const sf::Vector2f &init_pos, const Sprite_state_machine_node sprite_state_machine[]);

    void update(float delta_t) override;
};
