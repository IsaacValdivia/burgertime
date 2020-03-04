#include "BurgerTimeStateMachine.hpp"
#include "BurgerTimeController.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>


constexpr std::array<uint8_t, BurgerTimeStateMachine::NUM_STATES> BurgerTimeStateMachine::stateWaitTime;
constexpr std::array<BurgerTimeStateMachine::State, BurgerTimeStateMachine::NUM_STATES> BurgerTimeStateMachine::stateNextState;

BurgerTimeStateMachine::BurgerTimeStateMachine()
: controller(BurgerTimeController::get()), currentState(initialState)
{
    transitionStateLogic[currentState]();
}

void BurgerTimeStateMachine::execute()
{
    onStateLogic[currentState]();
}

void BurgerTimeStateMachine::checkNextTimedGameState()
{
    auto elapsedTime = controller.logicClock.getElapsedTime();
    if (elapsedTime.asSeconds() >= BurgerTimeStateMachine::stateWaitTime[currentState])
    {
        controller.logicClock.restart();
        currentState = BurgerTimeStateMachine::stateNextState[currentState];
        transitionStateLogic[currentState]();
    }
}


// TODO: all transitions

void BurgerTimeStateMachine::onHighScoreScreen()
{
    checkNextTimedGameState();
}

void BurgerTimeStateMachine::transitionHighScoreScreen()
{
    controller.drawablesOnScreen.clear();
    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: High Score Screen");

    controller.drawablesOnScreen.push_back(text);
}


void BurgerTimeStateMachine::onItemPointsScreen()
{
    checkNextTimedGameState();
}

void BurgerTimeStateMachine::transitionItemPointsScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Item Points Screen");

    controller.drawablesOnScreen.push_back(text);
}


void BurgerTimeStateMachine::onCharacterScreen()
{
    checkNextTimedGameState();
}

void BurgerTimeStateMachine::transitionCharacterScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Character Screen");

    controller.drawablesOnScreen.push_back(text);
}


void BurgerTimeStateMachine::onFirstTutorialVidScreen()
{
    checkNextTimedGameState();
}

void BurgerTimeStateMachine::transitionFirstTutorialVidScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: First Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
}


void BurgerTimeStateMachine::onSecondTutorialVidScreen()
{
    checkNextTimedGameState();
}

void BurgerTimeStateMachine::transitionSecondTutorialVidScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Second Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
}


void BurgerTimeStateMachine::onTutorialScreen()
{
    checkNextTimedGameState();
}

void BurgerTimeStateMachine::transitionTutorialScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Tutorial Screen");

    controller.drawablesOnScreen.push_back(text);
}


void BurgerTimeStateMachine::onThirdTutorialVidScreen()
{
    checkNextTimedGameState();
}

void BurgerTimeStateMachine::transitionThirdTutorialVidScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Third Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
}


void BurgerTimeStateMachine::onMainScreen()
{
    // TODO
}

void BurgerTimeStateMachine::transitionMainScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Main Screen");

    controller.drawablesOnScreen.push_back(text);
}
