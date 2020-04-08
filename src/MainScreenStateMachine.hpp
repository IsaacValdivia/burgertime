#pragma once

#include <tinyfsm.hpp>

#include <utility>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "Config.hpp"

class MainScreenStateMachine : public tinyfsm::MooreMachine<MainScreenStateMachine>
{
public:
    void react(const tinyfsm::Event &){};

    virtual void react(const ExecuteEvent &){};


protected:
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

class ConfigOptionState : public MainScreenStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class InsideConfigOptionState : public MainScreenStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class ResolutionScreenInsideState : public MainScreenStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;

    void changeResolutionsText() const;

    Config::Resolution current_resolution;
    bool isInExit;
};

class ResolutionScreenState : public MainScreenStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class BindingsScreenInsideState : public MainScreenStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class BindingsOptionState : public MainScreenStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class ResolutionOptionState : public MainScreenStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class BackOptionState : public MainScreenStateMachine
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
