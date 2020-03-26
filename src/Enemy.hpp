#pragma once

#include <SFML/Graphics.hpp>

#include "memory"
#include "Actor.hpp"
#include "IA.hpp"

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

    struct Sprite_state_machine {
        float sprite_duration;
        BT_sprites::Sprite sprites[NUM_ACTIONS];
    };

    static const Sprite_state_machine sausage_sprite_state_machine[];
    static const Sprite_state_machine egg_sprite_state_machine[];
    static const Sprite_state_machine pickle_sprite_state_machine[];

private:
    static constexpr float x_walking_speed = 60;
    static constexpr float y_walking_speed = x_walking_speed / 1.72;

    static constexpr float walking_sprite_duration = 0.08;
    static constexpr float dying_sprite_duration = 0.1;
    static constexpr float pepper_sprite_animation = 0.27;

    static constexpr float pepper_duration = 2;

    const Sprite_state_machine *const sprite_state_machine;

    float acc_delta_t_pepper;

    const Tile* aStarTile;
    Direction aStarDirection;

    Direction initial_direction;

    Action new_action;
    Action last_action;

    const IA &ia;

    void move(float &move_x, float &move_y, float delta_t);
public:
    Enemy(const sf::Vector2f &init_pos, const Sprite_state_machine sprite_state_machine[], std::shared_ptr<Map> map, const IA &ia, const Direction initial_direction);

    void pepper();

    void update(float delta_t) override;
};
