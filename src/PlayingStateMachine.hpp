#pragma once

#include "Bonus.hpp"
#include "BurgerTimeController.hpp"
#include "Constants.hpp"
#include "Enemy.hpp"
#include "Pepper.hpp"
#include "Player.hpp"

#include <list>
#include <SFML/Graphics.hpp>
#include <tinyfsm.hpp>

class PlayingStateMachine : public tinyfsm::MooreMachine<PlayingStateMachine> {
public:
    /**
     * @brief Main control function
     *
     */
    void react(const tinyfsm::Event &) {};

    virtual void react(const ExecuteEvent &) {};

    /**
     * @brief Returns true if there are remaining pepper usages
     *
     * @return true
     * @return false
     */
    bool has_pepper() const;

    /**
     * @brief Spawns the player and the enemies
     *
     */
    void add_player_and_enemies();

    /**
     * @brief Spawns an enemy of type type on a certain tile, with a certain offset w.r.t the tile
     *
     * @param type type of enemy to spawn
     * @param offset position offset
     */
    void spawn_enemy(const Enemy::Type &type, const Tile &, float offset);

    /**
     * @brief Checks and processes the collisions with ingredients
     *
     */
    void ingredient_collision();

    /**
     * @brief Adds points to the counter and increases the player's lives if required
     *
     * @param points number of points
     */
    void add_points(unsigned int points);

    /**
     * @brief Draws the pepper thrown on screen
     *
     * @param launch_position position from which its thrown
     * @param direction direction of the pepper
     */
    void add_pepper(const sf::Vector2f &launch_position, Direction direction);

    /**
     * @brief Sets pepper to nullptr
     *
     */
    void delete_pepper();

    /**
     * @brief Returns the current ingame score
     *
     * @return uint32_t score
     */
    static uint32_t get_current_score();

protected:
    class PepperCounter {
        uint8_t current_pepper;

    public:
        /**
         * @brief Construct a new Pepper Counter object
         *
         */
        PepperCounter();

        /**
         * @brief Increases pepper by change
         *
         * @param change increase
         */
        void change_pepper(int change);

        /**
         * @brief Returns true if there are peppers usages left
         *
         * @return true
         * @return false
         */
        bool has_pepper() const;
    };

    class LivesCounter {
        uint8_t current_lives;

    public:
        /**
         * @brief Construct a new Lives Counter object
         *
         */
        LivesCounter();

        /**
         * @brief Increase life counter by change
         *
         * @param change increase
         */
        void change_lives(int change);

        /**
         * @brief Returns true if there are any lives remaining
         *
         * @return true
         * @return false
         */
        bool has_lives() const;
    };

    class ScoreCounter {
        uint32_t current_score;
        uint32_t current_top_score;

    public:
        /**
         * @brief Construct a new Score Counter object
         *
         */
        ScoreCounter();

        /**
         * @brief Increases the point counter by points
         *
         * @param points increase
         */
        void add_points(uint32_t points);

        /**
         * @brief Returns the current ingame score
         *
         * @return uint32_t
         */
        uint32_t get_score() const;
    };

    class LevelCounter {
        uint32_t current_level;

    public:
        /**
         * @brief Construct a new Level Counter object
         *
         */
        LevelCounter();

        /**
         * @brief Increases level counter by level
         *
         * @param level increase
         */
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

    /**
     * @brief Sets the current game info
     *
     */
    void change_game_info();

    /**
     * @brief Changes game_info to new_game_info
     *
     * @param new_game_info new game information
     */
    void set_game_info(std::unique_ptr<GameInfo> new_game_info);

    std::unique_ptr<GameInfo> game_info;

    static BurgerTimeController &controller;
    static GUI &gui;
};

class EnterStatePlaying : public PlayingStateMachine {
    /**
     * @brief Entry state function
     *
     */
    void entry() override;

    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

class GameOverStatePlaying : public PlayingStateMachine {};

class GameReadyScreenState : public PlayingStateMachine {
    /**
     * @brief Entry state function
     *
     */
    void entry() override;

    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

class NormalStatePlaying : public PlayingStateMachine {
    /**
     * @brief Entry state function
     *
     */
    void entry() override;

    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;

    /**
     * @brief Checks if the main bgm has been played, if not, plays it
     *
     */
    void check_main_music();

    bool main_music_played;
    bool has_entered_level_first_time;
};

class WinStatePlaying : public PlayingStateMachine {
    /**
     * @brief Entry state function
     *
     */
    void entry() override;

    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

class DeadStatePlaying : public PlayingStateMachine {
    /**
     * @brief Entry state function
     *
     */
    void entry() override;

    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};
