#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "Actor.hpp"
#include "Map.hpp"

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

    Action last_direction; // LEFT, RIGHT, UP or DOWN only.

    Action last_action;

    std::shared_ptr<Map> map;

    bool won;

public:
    Player(const sf::Vector2f &init_pos, std::shared_ptr<Map> map);

    void update(float delta_t) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool has_won() const;

    void win();
};
