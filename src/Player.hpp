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

    static constexpr float x_walking_speed = 90;
    static constexpr float y_walking_speed = x_walking_speed / 1.72;

    static constexpr float walking_sprite_duration = 0.08;
    static constexpr float peppering_sprite_duration = 0.1;
    static constexpr float end_game_sprite_duration = 0.2;

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

    nod::unsafe_signal<void(const std::shared_ptr<Tile>)> player_moved;

public:
    Player(const sf::Vector2f &init_pos, std::shared_ptr<Map> map,
           const std::function<void(const sf::Vector2f &, Direction)> &pepper_spawned_func,
           const std::function<bool()> &has_pepper);

    void update(float delta_t) override;

    bool has_won() const;

    void win();

    bool going_x_direction();

    nod::connection connect_player_moved(
        const std::function<void(const std::shared_ptr<Tile>)> &player_moved_func);
};
