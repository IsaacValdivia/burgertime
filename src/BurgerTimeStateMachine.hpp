#pragma once

#include "BurgerTimeController.hpp"
#include "Constants.hpp"
#include "GUI.hpp"
#include "HighScores.hpp"

#include <tinyfsm.hpp>

class BurgerTimeStateMachine : public tinyfsm::MooreMachine<BurgerTimeStateMachine> {
protected:
    static BurgerTimeController &controller;
    static GUI &gui;
public:
    /**
     * @brief Main control function
     *
     */
    void react(const tinyfsm::Event &) {};

    virtual void react(const ExecuteEvent &) {};

    /**
     * @brief Reacts and refreshes timer if wait_time has elapsed
     *
     * @param wait_time
     * @return true
     * @return false
     */
    static bool timed_state_react(int wait_time);
};

class HighscoreDisplayScreenState : public BurgerTimeStateMachine {
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

class ItemPointsScreenState : public BurgerTimeStateMachine {
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

    std::array<std::shared_ptr<sf::Sprite>, 4> top_bun;
    std::array<std::shared_ptr<sf::Sprite>, 4> lettuce;
    std::array<std::shared_ptr<sf::Sprite>, 4> cheese;
    std::array<std::shared_ptr<sf::Sprite>, 4> burger;
    std::array<std::shared_ptr<sf::Sprite>, 4> tomato;
    std::array<std::shared_ptr<sf::Sprite>, 4> bot_bun;
    std::shared_ptr<sf::Sprite> ice_cream;
    std::shared_ptr<sf::Sprite> pt_500;
    std::shared_ptr<sf::Sprite> coffee;
    std::shared_ptr<sf::Sprite> pt_1000;
    std::shared_ptr<sf::Sprite> fries;
    std::shared_ptr<sf::Sprite> pt_1500;
    std::shared_ptr<sf::Sprite> pepper;
    std::shared_ptr<sf::Sprite> chef;
};

class MainScreenState : public BurgerTimeStateMachine {
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

class PlayingState : public BurgerTimeStateMachine {
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

class GameOverScreenState : public BurgerTimeStateMachine {
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

    static constexpr auto MAX_TEXTS = 8;
    static constexpr auto ANIMATION_FREQ = 0.2;
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

class EnterHighscoreState : public BurgerTimeStateMachine {
private:
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

    static constexpr auto ENTER_NAME_STR = "ENTER YOUR NAME";
    static constexpr auto HIGH_SCORE_TEXT_BASE = "enterHighScore_";

    static uint32_t new_high_score;
    int high_score_position;
    int char_position;

public:
    /**
     * @brief Sets new highscore
     *
     * @param new_high_score
     */
    static void set_high_score(uint32_t new_high_score);
};

class FinishedState : public BurgerTimeStateMachine {};
