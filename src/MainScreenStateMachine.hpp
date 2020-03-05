#pragma once

#include "StateMachine.hpp"
#include "Constants.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

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


    void transitionFinished();


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

    static constexpr auto START_SELECTION_POSITION = std::make_pair<int, int>(4 * WINDOW_WIDTH / 10 - 13, 3 * WINDOW_HEIGHT / 10);
    static constexpr auto EXIT_SELECTION_POSITION = std::make_pair<int, int>(4 * WINDOW_WIDTH / 10 - 13, 4 * WINDOW_HEIGHT / 10);

    static constexpr auto INITIAL_STATE = ENTER_STATE;

    std::array<State, NUM_STATES> stateNextState = {
        START_OPTION,
        EXIT_OPTION,
        START_OPTION,
    };

    BurgerTimeController &controller;
    State currentState;
    std::shared_ptr<sf::CircleShape> selectionTriangle;


    // TODO: const?
    const std::array<std::function<bool()>, NUM_STATES> onStateLogic = {
        nullptr,
        std::bind(&MainScreenStateMachine::onStartOption, this),
        std::bind(&MainScreenStateMachine::onExitOption, this),
        nullptr
    };

    // TODO: const?
    const std::array<std::function<void()>, NUM_STATES> transitionStateLogic = {
        std::bind(&MainScreenStateMachine::transitionEntered, this),
        std::bind(&MainScreenStateMachine::transitionStartOption, this),
        std::bind(&MainScreenStateMachine::transitionExitOption, this),
        std::bind(&MainScreenStateMachine::transitionFinished, this),
    };
};
