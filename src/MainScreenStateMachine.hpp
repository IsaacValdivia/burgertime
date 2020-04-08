#pragma once

#include <tinyfsm.hpp>

#include <utility>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "Audio.hpp"

class MainScreenStateMachine : public tinyfsm::MooreMachine<MainScreenStateMachine>
{
public:
    void react(const tinyfsm::Event &){};

    virtual void react(const ExecuteEvent &){};


protected:
    static constexpr auto START_SELECTION_POSITION = std::make_pair(32 * WINDOW_WIDTH / 100 - 13, 3 * WINDOW_HEIGHT / 10);
    static constexpr auto BINDINGS_SELECTION_POSITION = std::make_pair(32 * WINDOW_WIDTH / 100 - 13, 4 * WINDOW_HEIGHT / 10);
    static constexpr auto EXIT_SELECTION_POSITION = std::make_pair(32 * WINDOW_WIDTH / 100 - 13, 5 * WINDOW_HEIGHT / 10);

    static std::shared_ptr<sf::CircleShape> selectionTriangle;
    static BurgerTimeController &controller;
    static GUI &gui;
};

class EnterStateMainScreen : public MainScreenStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class StartOptionState : public MainScreenStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class BindingsOptionState : public MainScreenStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class ExitOptionState : public MainScreenStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class FinishedStartState : public MainScreenStateMachine
{
};

class FinishedExitState : public MainScreenStateMachine
{
};
