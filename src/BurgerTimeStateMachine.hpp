#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <functional>
#include "StateMachine.hpp"
#include "MainScreenStateMachine.hpp"

class BurgerTimeController;

class BurgerTimeStateMachine : public StateMachine
{
public:
    BurgerTimeStateMachine();

private:
    bool nextOnStateLogic();

    void nextTransitionStateLogic();

    void moveToNextState();

    bool checkNextTimedGameState();
    
    bool checkSkipGameState();


    bool onHighScoreScreen();

    void transitionHighScoreScreen();


    bool onItemPointsScreen();

    void transitionItemPointsScreen();


    bool onCharacterScreen();

    void transitionCharacterScreen();


    bool onFirstTutorialVidScreen();

    void transitionFirstTutorialVidScreen();


    bool onSecondTutorialVidScreen();

    void transitionSecondTutorialVidScreen();


    bool onTutorialScreen();

    void transitionTutorialScreen();


    bool onThirdTutorialVidScreen();

    void transitionThirdTutorialVidScreen();


    bool onGameReadyScreen();

    void transitionGameReadyScreen();


    // TODO: proper times etc

    enum State : uint8_t
    {
        HIGHSCORE_DISPLAY_SCREEN,
        ITEM_POINTS_SCREEN,
        CHARACTER_SCREEN,
        FIRST_TUTORIAL_VID_SCREEN,
        SECOND_TUTORIAL_VID_SCREEN,
        TUTORIAL_SCREEN,
        THIRD_TUTORIAL_VID_SCREEN,
        MAIN_SCREEN,
        GAME_READY_SCREEN,
        PLAYING_SCREEN,
        PAUSED_SCREEN,
        // ...
        NUM_STATES,
    };

    static constexpr auto INITIAL_STATE = HIGHSCORE_DISPLAY_SCREEN;

    static constexpr std::array<uint8_t, NUM_STATES> STATE_WAIT_TIME = {
        5,
        5,
        5,
        5,
        5,
        5,
        5,
        0,
        5,
    };

    static constexpr std::array<State, NUM_STATES> STATE_NEXT_STATE = {
        ITEM_POINTS_SCREEN,
        CHARACTER_SCREEN,
        FIRST_TUTORIAL_VID_SCREEN,
        SECOND_TUTORIAL_VID_SCREEN,
        TUTORIAL_SCREEN,
        THIRD_TUTORIAL_VID_SCREEN,
        MAIN_SCREEN,
        GAME_READY_SCREEN,
        PLAYING_SCREEN,
    };

    BurgerTimeController &controller;

    MainScreenStateMachine mainScreenStateMach;

    // TODO: const?
    const std::array<std::function<bool()>, NUM_STATES> onStateLogic = {
        std::bind(&BurgerTimeStateMachine::onHighScoreScreen, this),
        std::bind(&BurgerTimeStateMachine::onItemPointsScreen, this),
        std::bind(&BurgerTimeStateMachine::onCharacterScreen, this),
        std::bind(&BurgerTimeStateMachine::onFirstTutorialVidScreen, this),
        std::bind(&BurgerTimeStateMachine::onSecondTutorialVidScreen, this),
        std::bind(&BurgerTimeStateMachine::onTutorialScreen, this),
        std::bind(&BurgerTimeStateMachine::onThirdTutorialVidScreen, this),
        std::bind(&MainScreenStateMachine::mainStateMachineBinding, &mainScreenStateMach),
        std::bind(&BurgerTimeStateMachine::onGameReadyScreen, this),
    };

    // TODO: const?
    const std::array<std::function<void()>, NUM_STATES> transitionStateLogic = {
        std::bind(&BurgerTimeStateMachine::transitionHighScoreScreen, this),
        std::bind(&BurgerTimeStateMachine::transitionItemPointsScreen, this),
        std::bind(&BurgerTimeStateMachine::transitionCharacterScreen, this),
        std::bind(&BurgerTimeStateMachine::transitionFirstTutorialVidScreen, this),
        std::bind(&BurgerTimeStateMachine::transitionSecondTutorialVidScreen, this),
        std::bind(&BurgerTimeStateMachine::transitionTutorialScreen, this),
        std::bind(&BurgerTimeStateMachine::transitionThirdTutorialVidScreen, this),
        std::bind(&MainScreenStateMachine::initialize, &mainScreenStateMach),
        std::bind(&BurgerTimeStateMachine::transitionGameReadyScreen, this),
    };
};
