#pragma once

#include <tinyfsm.hpp>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "GUI.hpp"
#include "HighScores.hpp"

class BurgerTimeStateMachine : public tinyfsm::MooreMachine<BurgerTimeStateMachine>
{
public:
    void react(const tinyfsm::Event &){};

    virtual void react(const ExecuteEvent &){};

    static bool timedStateReact(int waitTime);

protected:
    static BurgerTimeController &controller;
    static GUI &gui;
};

class HighscoreDisplayScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;

};

class ItemPointsScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;


    std::array<std::shared_ptr<sf::Sprite>, 4> topBun;
    std::array<std::shared_ptr<sf::Sprite>, 4> lettuce;
    std::array<std::shared_ptr<sf::Sprite>, 4> cheese;
    std::array<std::shared_ptr<sf::Sprite>, 4> burger;
    std::array<std::shared_ptr<sf::Sprite>, 4> tomato;
    std::array<std::shared_ptr<sf::Sprite>, 4> botBun;
    std::shared_ptr<sf::Sprite> iceCream;
    std::shared_ptr<sf::Sprite> pt500;
    std::shared_ptr<sf::Sprite> coffee;
    std::shared_ptr<sf::Sprite> pt1000;
    std::shared_ptr<sf::Sprite> fries;
    std::shared_ptr<sf::Sprite> pt1500;
    std::shared_ptr<sf::Sprite> pepper;
    std::shared_ptr<sf::Sprite> chef;
};

class CharacterScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class FirstTutorialVidScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class SecondTutorialVidScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class TutorialScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class ThirdTutorialVidScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class MainScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class PlayingState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class GameOverScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;

    static constexpr auto MAX_TEXTS = 8;
    static constexpr auto ANIMATION_FREQ = 0.2;
    static constexpr std::array<const char*, MAX_TEXTS> DIFFERENT_TEXTS = {
        "G",
        "GA",
        "GAM",
        "GAME",
        "GAME O",
        "GAME OV",
        "GAME OVE",
        "GAME OVER"
    };

    int currentText;
};

class EnterHighscoreState : public BurgerTimeStateMachine
{
public:
    static void setHighScore(uint32_t newHighScore);

private:
    void entry() override;
    void react(const ExecuteEvent &) override;

    static constexpr auto ENTER_NAME_STR = "ENTER YOUR NAME";
    static constexpr auto HIGH_SCORE_TEXT_BASE = "enterHighScore_";
    static uint32_t newHighscore;
    int highScorePosition;
    int charPosition;
};

class FinishedState : public BurgerTimeStateMachine
{
};
