#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <functional>
#include "StateMachine.hpp"

class BurgerTimeController;

class BurgerTimeStateMachine : StateMachine
{
public:
    BurgerTimeStateMachine();

    void execute();

    void checkNextTimedGameState();


    void onHighScoreScreen();

    void transitionHighScoreScreen();


    void onItemPointsScreen();

    void transitionItemPointsScreen();


    void onCharacterScreen();

    void transitionCharacterScreen();


    void onFirstTutorialVidScreen();

    void transitionFirstTutorialVidScreen();


    void onSecondTutorialVidScreen();

    void transitionSecondTutorialVidScreen();


    void onTutorialScreen();

    void transitionTutorialScreen();


    void onThirdTutorialVidScreen();

    void transitionThirdTutorialVidScreen();


    void onMainScreen();

    void transitionMainScreen();


    void onGameReadyScreen();

    void transitionGameReadyScreen();

private:

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
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
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
    State currentState;

    // TODO: const?
    const std::array<std::function<void()>, NUM_STATES> onStateLogic = {
        std::bind(&BurgerTimeStateMachine::onHighScoreScreen, this),
        std::bind(&BurgerTimeStateMachine::onItemPointsScreen, this),
        std::bind(&BurgerTimeStateMachine::onCharacterScreen, this),
        std::bind(&BurgerTimeStateMachine::onFirstTutorialVidScreen, this),
        std::bind(&BurgerTimeStateMachine::onSecondTutorialVidScreen, this),
        std::bind(&BurgerTimeStateMachine::onTutorialScreen, this),
        std::bind(&BurgerTimeStateMachine::onThirdTutorialVidScreen, this),
        std::bind(&BurgerTimeStateMachine::onMainScreen, this),
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
        std::bind(&BurgerTimeStateMachine::transitionMainScreen, this),
        std::bind(&BurgerTimeStateMachine::transitionGameReadyScreen, this),
    };
};
