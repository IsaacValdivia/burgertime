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

    struct Sprite_state_machine {
        float sprite_duration;
        BT_sprites::Sprite sprites[NUM_ACTIONS];
    };

    static const Sprite_state_machine sprite_state_machine[];
    static const BT_sprites::Sprite pepper_sprite_state_machine[]; // Special case.

    Action new_action;
    Action last_action;

    bool won;

    std::function<void(const sf::Vector2f&, Direction)> pepper_spawned_func;

    nod::unsafe_signal<void(const std::shared_ptr<Tile>)> player_moved;

public:
    Player(const sf::Vector2f &init_pos, std::shared_ptr<Map> map, const std::function<void(const sf::Vector2f&, Direction)> &pepper_spawned_func);

    void update(float delta_t) override;

    bool has_won() const;

    void win();

    void connect_player_moved(const std::function<void(const std::shared_ptr<Tile>)> &player_moved_func);
};
