#pragma once

#include <tinyfsm.hpp>

#include <SFML/Graphics.hpp>
#include <list>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "Player.hpp"
#include "Pepper.hpp"
#include "Enemy.hpp"
#include "Bonus.hpp"

class PlayingStateMachine : public tinyfsm::MooreMachine<PlayingStateMachine> {
public:
    void react(const tinyfsm::Event &) {};

    virtual void react(const ExecuteEvent &) {};

    bool has_pepper() const;

    void add_player_and_enemies();

    void spawn_enemy(const Enemy::Type &type, const Tile &, float offset);

    void ingredient_collision();

    void add_points(unsigned int points);

    void add_pepper(const sf::Vector2f &launchPosition, Direction direction);

    void delete_pepper();

    static uint32_t get_current_score();

protected:
    class PepperCounter {
        uint8_t current_pepper;

    public:
        PepperCounter();

        void change_pepper(int change);
        bool has_pepper() const;
    };

    class LivesCounter {
        uint8_t current_lives;

    public:
        LivesCounter();

        void change_lives(int change);
        bool has_lives() const;
    };

    class ScoreCounter {
        uint32_t current_score;
        uint32_t current_top_score;

    public:
        ScoreCounter();

        void add_points(uint32_t points);
        uint32_t getScore() const;
    };

    class LevelCounter {
        uint32_t current_level;

    public:
        LevelCounter();

        void add_level(uint32_t level);
    };


    struct GameInfo {
        std::vector<std::shared_ptr<Map>> maps;

        std::shared_ptr<Player> player;
        std::shared_ptr<Pepper> pepper;

        std::shared_ptr<AI> ai;
        std::list<std::shared_ptr<Enemy>> enemies;

        std::shared_ptr<sf::Sprite> pepper_text;
        std::shared_ptr<sf::Sprite> lives_sprite;
        std::shared_ptr<sf::Sprite> level_sprite;

        std::shared_ptr<Bonus> bonus;

        std::array<std::shared_ptr<sf::RectangleShape>, 2> curtains;

        uint8_t current_ingredients;

        int points_to_extra_life;

        PepperCounter pepper_counter;
        LivesCounter lives_counter;
        ScoreCounter score_counter;
        LevelCounter level_counter;

        size_t current_map;

        bool has_just_entered;
    };

    void change_game_info();

    void set_game_info(std::unique_ptr<GameInfo> newGameInfo);

    std::unique_ptr<GameInfo> game_info;

    static BurgerTimeController &controller;
    static GUI &gui;
};

class EnterStatePlaying : public PlayingStateMachine {
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class GameOverStatePlaying : public PlayingStateMachine {};

class GameReadyScreenState : public PlayingStateMachine {
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class NormalStatePlaying : public PlayingStateMachine {
    void entry() override;
    void react(const ExecuteEvent &) override;

    void check_main_music();

    bool main_music_played;
    bool has_entered_level_first_time;
};

class WinStatePlaying : public PlayingStateMachine {
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class DeadStatePlaying : public PlayingStateMachine {
    void entry() override;
    void react(const ExecuteEvent &) override;
};
