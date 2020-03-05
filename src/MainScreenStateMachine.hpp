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

    std::pair<bool, uint32_t> mainStateMachineBinding();
private:
    std::pair<bool, uint32_t> nextOnStateLogic();

    void nextTransitionStateLogic();


    enum State
    {
        ENTER_STATE,
        START_OPTION,
        EXIT_OPTION,
        FINISHED_START_STATE,
        FINISHED_EXIT_STATE,
        NUM_STATES
    };


    std::pair<bool, State> onEntered();

    void transitionEntered();


    std::pair<bool, State> onFinished();
    
    void transitionFinished();


    std::pair<bool, State> onStartOption();

    void transitionStartOption();


    std::pair<bool, State> onExitOption();

    void transitionExitOption();



    static constexpr auto START_SELECTION_POSITION = std::make_pair(4 * WINDOW_WIDTH / 10 - 13, 3 * WINDOW_HEIGHT / 10);
    static constexpr auto EXIT_SELECTION_POSITION = std::make_pair(4 * WINDOW_WIDTH / 10 - 13, 4 * WINDOW_HEIGHT / 10);

    static constexpr auto INITIAL_STATE = ENTER_STATE;

    BurgerTimeController &controller;
    std::shared_ptr<sf::CircleShape> selectionTriangle;


    // TODO: const?
    const std::array<std::function<std::pair<bool, State>()>, NUM_STATES> onStateLogic = {
        std::bind(&MainScreenStateMachine::onEntered, this),
        std::bind(&MainScreenStateMachine::onStartOption, this),
        std::bind(&MainScreenStateMachine::onExitOption, this),
        std::bind(&MainScreenStateMachine::onFinished, this),
        std::bind(&MainScreenStateMachine::onFinished, this),
    };

    // TODO: const?
    const std::array<std::function<void()>, NUM_STATES> transitionStateLogic = {
        std::bind(&MainScreenStateMachine::transitionEntered, this),
        std::bind(&MainScreenStateMachine::transitionStartOption, this),
        std::bind(&MainScreenStateMachine::transitionExitOption, this),
        std::bind(&MainScreenStateMachine::transitionFinished, this),
        std::bind(&MainScreenStateMachine::transitionFinished, this),
    };
};
