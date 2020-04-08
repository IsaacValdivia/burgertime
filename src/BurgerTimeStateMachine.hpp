#pragma once

#include <tinyfsm.hpp>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "GUI.hpp"
#include "HighScores.hpp"

class BurgerTimeStateMachine : public tinyfsm::MooreMachine<BurgerTimeStateMachine> {
public:
    /**
     * @brief Main control function
     *
     */
    void react(const tinyfsm::Event &) {};

    /**
     * @brief Main control function
     *
     */
    virtual void react(const ExecuteEvent &) {};

    /**
     * @brief Checks whether paused has been pressed and restarts the timer if
     *        wait_time has been reached
     *
     * @param wait_time
     * @return true
     * @return false
     */
    static bool timed_state_react(int wait_time);

protected:
    static BurgerTimeController &controller; // reference to controller object
    static GUI &gui; // reference to gui object
};

/**
 * @brief State machine for highscores screen
 *
 */
class HighscoreDisplayScreenState : public BurgerTimeStateMachine {
    /**
     * @brief Called when initial state is entered
     *
     */
    void entry() override;
    void react(const ExecuteEvent &) override;

};

/**
 * @brief State machine for item points screen
 *
 */
class ItemPointsScreenState : public BurgerTimeStateMachine {
    /**
     * @brief Called when initial state is entered
     *
     */
    void entry() override;

    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;

    // Arrays of different Sprites for the item animations
    std::array<std::shared_ptr<sf::Sprite>, 4> top_bun;
    std::array<std::shared_ptr<sf::Sprite>, 4> lettuce;
    std::array<std::shared_ptr<sf::Sprite>, 4> cheese;
    std::array<std::shared_ptr<sf::Sprite>, 4> burger;
    std::array<std::shared_ptr<sf::Sprite>, 4> tomato;
    std::array<std::shared_ptr<sf::Sprite>, 4> botBun;
    std::shared_ptr<sf::Sprite> ice_cream;
    std::shared_ptr<sf::Sprite> pt_500;
    std::shared_ptr<sf::Sprite> coffee;
    std::shared_ptr<sf::Sprite> pt_1000;
    std::shared_ptr<sf::Sprite> fries;
    std::shared_ptr<sf::Sprite> pt_1500;
    std::shared_ptr<sf::Sprite> pepper;
    std::shared_ptr<sf::Sprite> chef;
};

/**
 * @brief State machine for character screen
 *
 */
class CharacterScreenState : public BurgerTimeStateMachine {
    /**
     * @brief Called when initial state is entered
     *
     */
    void entry() override;

    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

/**
 * @brief State machine for 1st tutorial screen
 *
 */
class FirstTutorialVidScreenState : public BurgerTimeStateMachine {
    /**
     * @brief Called when initial state is entered
     *
     */
    void entry() override;
    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

/**
 * @brief State machine for 2nd tutorial screen
 *
 */
class SecondTutorialVidScreenState : public BurgerTimeStateMachine {
    /**
     * @brief Called when initial state is entered
     *
     */
    void entry() override;
    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

/**
 * @brief State machine for tutorial screens
 *
 */
class TutorialScreenState : public BurgerTimeStateMachine {
    /**
     * @brief Called when initial state is entered
     *
     */
    void entry() override;
    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

/**
 * @brief State machine for 3rd tutorial screens
 *
 */
class ThirdTutorialVidScreenState : public BurgerTimeStateMachine {
    /**
     * @brief Called when initial state is entered
     *
     */
    void entry() override;
    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

/**
 * @brief State machine for main game screen
 *
 */
class MainScreenState : public BurgerTimeStateMachine {
    /**
     * @brief Called when initial state is entered
     *
     */
    void entry() override;
    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

/**
 * @brief State machine for main game screen
 *
 */
class PlayingState : public BurgerTimeStateMachine {
    /**
     * @brief Called when initial state is entered
     *
     */
    void entry() override;
    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

/**
 * @brief State machine for game over screen
 *
 */
class GameOverScreenState : public BurgerTimeStateMachine {
    /**
     * @brief Called when initial state is entered
     *
     */
    void entry() override;
    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;

    static constexpr auto MAX_TEXTS = 8; // Max number of different texts
    static constexpr auto ANIMATION_FREQ = 0.2; // Seconds per text
    static constexpr std::array<const char *, MAX_TEXTS> DIFFERENT_TEXTS = {
        "G",
        "GA",
        "GAM",
        "GAME",
        "GAME O",
        "GAME OV",
        "GAME OVE",
        "GAME OVER"
    };

    int current_text;
};

/**
 * @brief State machine for entering highscores
 *
 */
class EnterHighScoreState : public BurgerTimeStateMachine {
public:
    static void set_high_score(uint32_t new_high_score);

private:
    void entry() override;
    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;

    static constexpr auto ENTER_NAME_STR = "ENTER YOUR NAME";
    static constexpr auto HIGH_SCORE_TEXT_BASE = "enterHighScore_";
    static uint32_t new_high_score;
    int high_score_position;
    int char_position;
};

/**
 * @brief State machine for end of game
 *
 */
class Finished_state : public BurgerTimeStateMachine {
};
