#include "MainScreenStateMachine.hpp"

#include <memory>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"

constexpr std::array<MainScreenStateMachine::State, MainScreenStateMachine::NUM_STATES> MainScreenStateMachine::STATE_NEXT_STATE;

MainScreenStateMachine::MainScreenStateMachine() 
: StateMachine(INITIAL_STATE), controller(BurgerTimeController::get())
{}

bool MainScreenStateMachine::nextOnStateLogic()
{
    return onStateLogic[currentState]();
}

void MainScreenStateMachine::nextTransitionStateLogic()
{
    transitionStateLogic[currentState]();
}

void MainScreenStateMachine::moveToNextState()
{
    currentState = MainScreenStateMachine::STATE_NEXT_STATE[currentState];
    nextTransitionStateLogic();
}

bool MainScreenStateMachine::mainStateMachineBinding()
{
    execute();

    return currentState == FINISHED_STATE;
}

void MainScreenStateMachine::transitionEntered()
{
    controller.drawablesOnScreen.clear();

    auto startText = std::make_shared<sf::Text>();
    startText->setFont(controller.font);
    startText->setString("START");
    startText->setScale(0.8, 0.8);
    startText->setPosition(4 * WINDOW_WIDTH / 10, 3 * WINDOW_HEIGHT / 10);

    auto exitText = std::make_shared<sf::Text>();
    exitText->setFont(controller.font);
    exitText->setString("EXIT");
    exitText->setScale(0.8, 0.8);
    exitText->setPosition(4 * WINDOW_WIDTH / 10, 4 * WINDOW_HEIGHT / 10);

    controller.drawablesOnScreen.push_back(startText);
    controller.drawablesOnScreen.push_back(exitText);

    currentState = START_OPTION;
}


bool MainScreenStateMachine::onStartOption()
{}

void MainScreenStateMachine::transitionStartOption()
{}


bool MainScreenStateMachine::onExitOption()
{}

void MainScreenStateMachine::transitionExitOption()
{}
