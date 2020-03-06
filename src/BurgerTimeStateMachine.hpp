#pragma once

#include <tinyfsm.hpp>
#include "Constants.hpp"

class BurgerTimeStateMachine : public tinyfsm::MooreMachine<BurgerTimeStateMachine>
{
public:
    void react(const tinyfsm::Event &){};

    virtual void react(const ExecuteEvent &) = 0;

    virtual int getWaitTime() { return 0; };

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
};

class HighscoreDisplayScreenState : public BurgerTimeStateMachine
{
private:
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() override { return 5; }
};

class ItemPointsScreenState : public BurgerTimeStateMachine
{
private:
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() override { return 5; }
};

class CharacterScreenState : public BurgerTimeStateMachine
{
private:
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() override { return 5; }
};

class FirstTutorialVidScreenState : public BurgerTimeStateMachine
{
private:
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() override { return 5; }
};

class SecondTutorialVidScreenState : public BurgerTimeStateMachine
{
private:
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() override { return 5; }
};

class TutorialScreenState : public BurgerTimeStateMachine
{
private:
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() override { return 5; }
};

class ThirdTutorialVidScreenState : public BurgerTimeStateMachine
{
private:
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() override { return 5; }
};

class MainScreenState : public BurgerTimeStateMachine
{
private:
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class GameReadyScreenState : public BurgerTimeStateMachine
{
private:
    void entry() override;
    void react(const ExecuteEvent &) override;

    int getWaitTime() override { return 5; }
};