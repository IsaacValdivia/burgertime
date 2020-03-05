#pragma once

#include "StateMachine.hpp"

class BurgerTimeController;

class MainScreenStateMachine : public StateMachine
{
public:
    MainScreenStateMachine();

    bool mainStateMachineBinding();

    bool nextOnStateLogic();

    void nextTransitionStateLogic();

    void moveToNextState();


    void transitionEntered();


    bool onStartOption();

    void transitionStartOption();


    bool onExitOption();

    void transitionExitOption();

private:
    enum State : uint8_t
    {
        ENTER_STATE,
        START_OPTION,
        EXIT_OPTION,
        FINISHED_STATE,
        NUM_STATES
    };

    static constexpr auto INITIAL_STATE = ENTER_STATE;

    static constexpr std::array<State, NUM_STATES> STATE_NEXT_STATE = {
        START_OPTION,
        EXIT_OPTION,
        START_OPTION,
    };

    BurgerTimeController &controller;
    State currentState;

    // TODO: const?
    const std::array<std::function<bool()>, NUM_STATES> onStateLogic = {
        nullptr,
        std::bind(&MainScreenStateMachine::onStartOption, this),
        std::bind(&MainScreenStateMachine::onExitOption, this),
    };

    // TODO: const?
    const std::array<std::function<void()>, NUM_STATES> transitionStateLogic = {
        std::bind(&MainScreenStateMachine::transitionEntered, this),
        std::bind(&MainScreenStateMachine::transitionStartOption, this),
        std::bind(&MainScreenStateMachine::transitionExitOption, this),
    };
};
