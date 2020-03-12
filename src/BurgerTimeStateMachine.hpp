#pragma once

#include <tinyfsm.hpp>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"

class BurgerTimeStateMachine : public tinyfsm::MooreMachine<BurgerTimeStateMachine>
{
public:
    void react(const tinyfsm::Event &){};

    virtual void react(const ExecuteEvent &){};

    virtual int getWaitTime() const { return 0; };

    bool timedStateReact();

    void highscoreDisplayScreenStateEntry();
    void itemPointsScreenStateEntry();
    void characterScreenStateEntry();
    void firstTutorialVidScreenStateEntry();
    void secondTutorialVidScreenStateEntry();
    void tutorialScreenStateEntry();
    void thirdTutorialVidScreenStateEntry();
    void gameReadyScreenState();

protected:
    static BurgerTimeController &controller;
};

class HighscoreDisplayScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() const override { return 500; }
};

class ItemPointsScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() const override { return 500; }
};

class CharacterScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() const override { return 5; }
};

class FirstTutorialVidScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() const override { return 5; }
};

class SecondTutorialVidScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() const override { return 5; }
};

class TutorialScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() const override { return 5; }
};

class ThirdTutorialVidScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() const override { return 5; }
};

class MainScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class GameReadyScreenState : public BurgerTimeStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() const override { return 5; }
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
    std::shared_ptr<sf::Text> text;
};

class FinishedState : public BurgerTimeStateMachine
{
};