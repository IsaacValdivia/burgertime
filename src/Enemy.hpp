#pragma once

#include "Actor.hpp"
#include "Audio.hpp"
#include "Tile.hpp"

#include <nod.hpp>
#include <memory>
#include <SFML/Graphics.hpp>

class AI;

class Enemy : public Actor {
public:
    enum Type : char {
        SAUSAGE = 'S',
        PICKLE = 'P',
        EGG = 'E',
    };

private:
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

    struct SpriteStateMachine {
        float sprite_duration;
        BtSprites::Sprite sprites[NUM_ACTIONS];
    };

    static const SpriteStateMachine sausage_sprite_state_machine[];
    static const SpriteStateMachine egg_sprite_state_machine[];
    static const SpriteStateMachine pickle_sprite_state_machine[];

    const float x_walking_speed = 60;
    const float y_walking_speed = x_walking_speed / 1.72;

    static constexpr float after_dead_sprite_duration = 1;

    static constexpr float walking_sprite_duration = 0.08;
    static constexpr float dying_sprite_duration = 0.16;
    static constexpr float pepper_sprite_animation = 0.27;

    static constexpr float rand_mov_prob_normalizer = 0.20;

    static constexpr float pepper_duration = 4;

    const SpriteStateMachine *sprite_state_machine;

    float acc_delta_t_pepper;

    bool random_sometimes;

    std::shared_ptr<const Tile> a_star_tile;
    Direction a_star_direction;

    const Direction initial_direction;

    int dead_points;

    bool initial_movement;
    bool after_dead;

    bool totally_dead;

    Action new_action;
    Action last_action;

    const Type type;

    const AI &ia;

    std::unique_ptr<nod::connection> ingredient_moving_connection;
    std::unique_ptr<nod::connection> stop_surfing_connection;

    std::function<void(unsigned int)> points_added;

    /**
     * @brief Moves the enemy by a certain offset, in function of delta_t
     *
     * @param move_x X offset
     * @param move_y Y offset
     * @param delta_t delta_t
     */
    void move(float &move_x, float &move_y, const float delta_t);

    /**
     * @brief Performs a random movement
     *
     * @param delta_t delta_t
     * @param current current tile
     */
    void random_move(const float delta_t, const Tile &current);
public:
    /**
     * @brief Construct a new Enemy object
     *
     * @param type type of enemy, namely egg, pickle or sausage
     * @param init_pos initial enemy position on the map
     * @param map pointer to map
     * @param ia ia that will govern the enemy
     * @param initial_direction initial direction taken by the enemy
     * @param points_added points gainable if killed
     * @param random_something should move randomly sometimes
     */
    Enemy(const Type &type, const sf::Vector2f &init_pos,
          const std::shared_ptr<Map> map,
          const AI &ia, const Direction initial_direction,
          const float x_walking_speed,
          const std::function<void(unsigned int)> &points_added, bool random_sometimes);

    /**
     * @brief Sets state to peppered and plays the pepper sound effect
     *
     */
    void pepper();

    /**
     * @brief Starts the binding of the enemy to the ingredient below
     *
     * @param ingredient_moving_con connection function with ingredient_moving
     * @param stop_surfing_con disable connection function
     * @param dead_points Points if dead
     */
    void start_surfing(nod::connection &&ingredient_moving_con,
                       nod::connection &&stop_surfing_con, const int dead_points);

    /**
     * @brief Cancels the binding of the enemy to the ingredient below
     *
     */
    void stop_surfing();

    /**
     * @brief Checks whether the enemy is peppered or not
     *
     * @return true
     * @return false
     */
    bool is_peppered() const;

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
     * @brief Get the Type of the enemy
     *
     * @return Type
     */
    Type get_type() const;

    /**
     * @brief Checks whether the enemy's state is completely dead
     *
     */
    bool completely_dead() const;

    /**
     * @brief Moves the enemy accordingly to y offset
     *
     * @param y Y offset
     */
    void move_by_signal(const float y);

    /**
     * @brief Main control function
     *
     * @param delta_t delta_t
     */
    void update(const float delta_t) override;
};
