#pragma once

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>

#include "nod.hpp"
#include "Actor.hpp"
#include "Map.hpp"
#include "Constants.hpp"

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

    static constexpr float x_walking_speed = 90; // Horizontal speed of the chef
    static constexpr float y_walking_speed = x_walking_speed / 1.72; // Vertical speed of the chef

    static constexpr float walking_sprite_duration = 0.08; // Duration of walking animation
    static constexpr float peppering_sprite_duration = 0.1; // Duration of pepper animation
    static constexpr float end_game_sprite_duration = 0.2; // Duration of end game animation

    struct SpriteStateMachine {
        float sprite_duration;
        BtSprites::Sprite sprites[NUM_ACTIONS];
    };

    static const SpriteStateMachine sprite_state_machine[];
    static const BtSprites::Sprite pepper_sprite_state_machine[]; // Special case.

    Action new_action;
    Action last_action;

    bool won;

    std::function<void(const sf::Vector2f &, Direction)> pepper_spawned_func;

    std::function<bool()> has_pepper;

    nod::unsafe_signal<void(const std::shared_ptr<Tile>, Direction)> player_moved;

public:
    /**
     * @brief Construct a new Player object
     *
     * @param init_pos initial player position
     * @param map map of the player
     * @param pepper_spawned_func callback for pepper
     * @param has_pepper callback for has_pepper
     */
    Player(const sf::Vector2f &init_pos, const std::shared_ptr<Map> map,
           const std::function<void(const sf::Vector2f &, Direction)> &pepper_spawned_func,
           const std::function<bool()> &has_pepper);

    /**
     * @brief Main control function
     *
     * @param delta_t delta_t
     */
    void update(const float delta_t) override;

    /**
     * @brief Returns if the player has won a level
     *
     * @return true
     * @return false
     */
    bool has_won() const;

    /**
     * @brief Sets won to true
     *
     */
    void win();

    /**
     * @brief Returns if the player is moving horizontally
     *
     * @return true
     * @return false
     */
    bool going_x_direction() const;

    /**
     * TODO
     *
     * @param player_moved_func
     * @return nod::connection
     */
    nod::connection connect_player_moved(
        const std::function<void(const std::shared_ptr<Tile>, Direction)> &player_moved_func);
};
