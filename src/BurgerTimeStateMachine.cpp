#include "BurgerTimeStateMachine.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "BurgerTimeController.hpp"
#include "Constants.hpp"
#include "InputSystem.hpp"


constexpr std::array<uint8_t, BurgerTimeStateMachine::NUM_STATES> BurgerTimeStateMachine::STATE_WAIT_TIME;
constexpr std::array<BurgerTimeStateMachine::State, BurgerTimeStateMachine::NUM_STATES> BurgerTimeStateMachine::STATE_NEXT_STATE;

BurgerTimeStateMachine::BurgerTimeStateMachine()
: StateMachine(INITIAL_STATE), controller(BurgerTimeController::get())
{
}

bool BurgerTimeStateMachine::nextOnStateLogic()
{
    return onStateLogic[currentState]();
}

void BurgerTimeStateMachine::nextTransitionStateLogic()
{
    transitionStateLogic[currentState]();
}

void BurgerTimeStateMachine::moveToNextState()
{
    currentState = BurgerTimeStateMachine::STATE_NEXT_STATE[currentState];
    nextTransitionStateLogic();
}

bool BurgerTimeStateMachine::checkNextTimedGameState()
{
    auto elapsedTime = controller.logicClock.getElapsedTime();
    if (elapsedTime.asSeconds() >= BurgerTimeStateMachine::STATE_WAIT_TIME[currentState])
    {
        controller.logicClock.restart();

        return true;
    }

    return false;
}

bool BurgerTimeStateMachine::checkSkipGameState()
{
    if (hasInputJustBeenPressed(InputSystem::Input::PAUSE))
    {
        controller.logicClock.restart();

        return true;
    }

    return false;
}



// TODO: all transitions

bool BurgerTimeStateMachine::onHighScoreScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return hasStateFinished;
}

void BurgerTimeStateMachine::transitionHighScoreScreen()
{
    controller.drawablesOnScreen.clear();
    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: High Score Screen");

    controller.drawablesOnScreen.push_back(text);
}


bool BurgerTimeStateMachine::onItemPointsScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return hasStateFinished;
}

void BurgerTimeStateMachine::transitionItemPointsScreen()
{
    controller.drawablesOnScreen.clear();

    auto burgerTimeText = std::make_shared<sf::Text>();
    burgerTimeText->setFillColor(sf::Color::Red);
    burgerTimeText->setFont(controller.font);
    burgerTimeText->setString("BURGER TIME");
    burgerTimeText->setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4);

    auto todoText = std::make_shared<sf::Text>();
    todoText->setFont(controller.font);
    todoText->setString("TODO: item points screen");
    todoText->setPosition(WINDOW_WIDTH / 5, WINDOW_HEIGHT / 3);

    controller.drawablesOnScreen.push_back(burgerTimeText);
    controller.drawablesOnScreen.push_back(todoText);
}


bool BurgerTimeStateMachine::onCharacterScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return hasStateFinished;
}

void BurgerTimeStateMachine::transitionCharacterScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Character Screen");

    controller.drawablesOnScreen.push_back(text);
}


bool BurgerTimeStateMachine::onFirstTutorialVidScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return hasStateFinished;
}

void BurgerTimeStateMachine::transitionFirstTutorialVidScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: First Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
}


bool BurgerTimeStateMachine::onSecondTutorialVidScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return hasStateFinished;
}

void BurgerTimeStateMachine::transitionSecondTutorialVidScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Second Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
}


bool BurgerTimeStateMachine::onTutorialScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return hasStateFinished;
}

void BurgerTimeStateMachine::transitionTutorialScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Tutorial Screen");

    controller.drawablesOnScreen.push_back(text);
}


bool BurgerTimeStateMachine::onThirdTutorialVidScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return hasStateFinished;
}

void BurgerTimeStateMachine::transitionThirdTutorialVidScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Third Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
}


bool BurgerTimeStateMachine::onGameReadyScreen()
{
    return false;
}

void BurgerTimeStateMachine::transitionGameReadyScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("GAME READY");
    text->setScale(0.8, 0.8);
    text->setPosition(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2);

    controller.drawablesOnScreen.push_back(text);
}
