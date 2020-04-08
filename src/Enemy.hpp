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

    struct SpriteStateMachine {
        float sprite_duration;
        BtSprites::Sprite sprites[NUM_ACTIONS];
    };

    static const SpriteStateMachine sausage_sprite_state_machine[];
    static const SpriteStateMachine egg_sprite_state_machine[];
    static const SpriteStateMachine pickle_sprite_state_machine[];

private:
    static constexpr float x_walking_speed = 60;
    static constexpr float y_walking_speed = x_walking_speed / 1.72;

    static constexpr float after_dead_sprite_duration = 1;

    static constexpr float walking_sprite_duration = 0.08;
    static constexpr float dying_sprite_duration = 0.16;
    static constexpr float pepper_sprite_animation = 0.27;

    static constexpr float rand_mov_prob_normalizer = 0.20;

    static constexpr float pepper_duration = 4;

    const SpriteStateMachine *const sprite_state_machine;

    float acc_delta_t_pepper;

    std::shared_ptr<Tile> a_star_tile;
    Direction a_star_direction;

    Direction initial_direction;

    int dead_points;

    bool initial_movement;
    bool after_dead;

    bool totally_dead;

    Action new_action;
    Action last_action;

    Type type;

    const AI &ia;

    std::unique_ptr<nod::connection> ingredient_moving_connection;
    std::unique_ptr<nod::connection> stop_surfing_connection;

    std::function<void(unsigned int)> points_added;

    /**
     * @brief Moves the enemy by a certain offset, in function of delta_t
     *
     * @param move_x
     * @param move_y
     * @param delta_t
     */
    void move(float &move_x, float &move_y, float delta_t);

    /**
     * @brief Performs a random movement
     *
     * @param delta_t
     * @param current
     */
    void random_move(const float delta_t, const Tile &current);
public:
    /**
     * @brief Construct a new Enemy object
     *
     * @param type
     * @param init_pos
     * @param sprite_state_machine
     * @param map
     * @param ia
     * @param initial_direction
     * @param points_added
     */
    Enemy(const Type &type, const sf::Vector2f &init_pos, const SpriteStateMachine
          sprite_state_machine[], std::shared_ptr<Map> map, const AI &ia,
          const Direction initial_direction,
          const std::function<void(unsigned int)> &points_added);

    /**
     * @brief Sets state to peppered and plays the pepper sound effect
     *
     */
    void pepper();

    /**
     * @brief Starts the binding of the enemy to the ingredient below
     *
     * @param ingredient_moving_con
     * @param stop_surfing_con
     * @param dead_points
     */
    void start_surfing(nod::connection &&ingredient_moving_con,
                       nod::connection &&stop_surfing_con, const int dead_points);

    /**
     * @brief Cancels the binding of the enemy to the ingredient below
     *
     */
    void stop_surfing();

    /**
     * @brief Moves the enemy accordingly to y offset
     *
     * @param y
     */
    void move_by_signal(const float y);

    /**
     * @brief Checks whether the enemy's state is completely dead
     *
     */
    bool completely_dead();

    /**
     * @brief Kills the enemy and plays the die sound effect
     *
     */
    void die() override;

    /**
     * @brief Checks whether the enemy is surfing or not
     *
     * @return true
     * @return false
     */
    bool is_surfing() const;

    /**
     * @brief Checks whether the enemy is peppered or not
     *
     * @return true
     * @return false
     */
    bool is_peppered() const;

    /**
     * @brief Get the Type of the enemy
     *
     * @return Type
     */
    Type get_type() const;

    /**
     * @brief Main control function
     *
     * @param delta_t
     */
    void update(float delta_t) override;
};
