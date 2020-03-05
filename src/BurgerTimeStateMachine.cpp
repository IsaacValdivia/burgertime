#include "BurgerTimeStateMachine.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "BurgerTimeController.hpp"
#include "Constants.hpp"
#include "InputSystem.hpp"


constexpr std::array<uint8_t, BurgerTimeStateMachine::NUM_STATES> BurgerTimeStateMachine::STATE_WAIT_TIME;

BurgerTimeStateMachine::BurgerTimeStateMachine()
: StateMachine(INITIAL_STATE), controller(BurgerTimeController::get())
{
}

std::pair<bool, uint32_t> BurgerTimeStateMachine::nextOnStateLogic()
{
    return onStateLogic[currentState]();
}

void BurgerTimeStateMachine::nextTransitionStateLogic()
{
    transitionStateLogic[currentState]();
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

std::pair<bool, uint32_t> BurgerTimeStateMachine::onHighScoreScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return std::make_pair(hasStateFinished, ITEM_POINTS_SCREEN);
}

void BurgerTimeStateMachine::transitionHighScoreScreen()
{
    controller.drawablesOnScreen.clear();
    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: High Score Screen");

    controller.drawablesOnScreen.push_back(text);
}


std::pair<bool, uint32_t> BurgerTimeStateMachine::onItemPointsScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return std::make_pair(hasStateFinished, CHARACTER_SCREEN);
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


std::pair<bool, uint32_t> BurgerTimeStateMachine::onCharacterScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return std::make_pair(hasStateFinished, FIRST_TUTORIAL_VID_SCREEN);
}

void BurgerTimeStateMachine::transitionCharacterScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Character Screen");

    controller.drawablesOnScreen.push_back(text);
}


std::pair<bool, uint32_t> BurgerTimeStateMachine::onFirstTutorialVidScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return std::make_pair(hasStateFinished, SECOND_TUTORIAL_VID_SCREEN);
}

void BurgerTimeStateMachine::transitionFirstTutorialVidScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: First Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
}


std::pair<bool, uint32_t> BurgerTimeStateMachine::onSecondTutorialVidScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return std::make_pair(hasStateFinished, TUTORIAL_SCREEN);
}

void BurgerTimeStateMachine::transitionSecondTutorialVidScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Second Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
}


std::pair<bool, uint32_t> BurgerTimeStateMachine::onTutorialScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return std::make_pair(hasStateFinished, THIRD_TUTORIAL_VID_SCREEN);
}

void BurgerTimeStateMachine::transitionTutorialScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Tutorial Screen");

    controller.drawablesOnScreen.push_back(text);
}


std::pair<bool, uint32_t> BurgerTimeStateMachine::onThirdTutorialVidScreen()
{
    bool hasStateFinished = checkSkipGameState();
    if (!hasStateFinished) 
    {
        hasStateFinished = checkNextTimedGameState();
    }

    return std::make_pair(hasStateFinished, MAIN_SCREEN);
}

void BurgerTimeStateMachine::transitionThirdTutorialVidScreen()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Third Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
}


std::pair<bool, uint32_t> BurgerTimeStateMachine::onGameReadyScreen()
{
    return std::make_pair(false, PLAYING_SCREEN);
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
