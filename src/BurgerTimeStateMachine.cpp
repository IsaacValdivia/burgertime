#include "BurgerTimeStateMachine.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "BurgerTimeController.hpp"
#include "Constants.hpp"


constexpr std::array<uint8_t, BurgerTimeStateMachine::NUM_STATES> BurgerTimeStateMachine::STATE_WAIT_TIME;
constexpr std::array<BurgerTimeStateMachine::State, BurgerTimeStateMachine::NUM_STATES> BurgerTimeStateMachine::STATE_NEXT_STATE;

BurgerTimeStateMachine::BurgerTimeStateMachine()
: controller(BurgerTimeController::get()), currentState(INITIAL_STATE)
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
    if (elapsedTime.asSeconds() >= BurgerTimeStateMachine::STATE_WAIT_TIME[currentState])
    {
        controller.logicClock.restart();
        currentState = BurgerTimeStateMachine::STATE_NEXT_STATE[currentState];
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
    checkNextTimedGameState();
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


void BurgerTimeStateMachine::onGameReadyScreen()
{

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
