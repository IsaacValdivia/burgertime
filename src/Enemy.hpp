#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include "Audio.hpp"
#include "Actor.hpp"
#include "AI.hpp"

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

    enum Type : char {
        SAUSAGE = 'S',
        PICKLE = 'P',
        EGG = 'E',
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

    static constexpr float after_dead_sprite_duration = 1;

    static constexpr float walking_sprite_duration = 0.08;
    static constexpr float dying_sprite_duration = 0.16;
    static constexpr float pepper_sprite_animation = 0.27;

    static constexpr float pepper_duration = 4;

    const Sprite_state_machine *sprite_state_machine;

    float acc_delta_t_pepper;

    std::shared_ptr<Tile> aStarTile;
    Direction aStarDirection;

    Direction initial_direction;

    int dead_points;

    bool initialMovement;
    bool after_dead;

    bool totallyDead;

    Action new_action;
    Action last_action;

    Type type;

    const AI &ia;

    std::unique_ptr<nod::connection> ingredient_moving_connection;
    std::unique_ptr<nod::connection> stop_surfing_connection;

    std::function<void(unsigned int)> points_added;

    void move(float &move_x, float &move_y, float delta_t);
public:
    Enemy(const Type &type, const sf::Vector2f &init_pos, std::shared_ptr<Map> map, const AI &ia, const Direction initial_direction, const std::function<void(unsigned int)> &points_added);

    void pepper();

    void start_surfing(nod::connection &&ingredient_moving_con, nod::connection &&stop_surfing_con, const int dead_points);

    void stop_surfing();

    void move_by_signal(const float y);

    bool completelyDead();

    void die() override;

    bool isSurfing() const;

    bool isPeppered() const;

    Type getType() const;

    void update(float delta_t) override;
};
