#include "MainScreenStateMachine.hpp"

#include "BurgerTimeController.hpp"
#include "InputSystem.hpp"


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
    currentState = stateNextState[currentState];
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

    selectionTriangle = std::make_shared<sf::CircleShape>(10, 3);
    selectionTriangle->setFillColor(sf::Color::White);
    selectionTriangle->setRotation(90);
    selectionTriangle->setPosition(START_SELECTION_POSITION.first, START_SELECTION_POSITION.second);

    controller.drawablesOnScreen.push_back(startText);
    controller.drawablesOnScreen.push_back(exitText);
    controller.drawablesOnScreen.push_back(selectionTriangle);

    currentState = START_OPTION;
}


void MainScreenStateMachine::transitionFinished()
{

}


bool MainScreenStateMachine::onStartOption()
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        stateNextState[START_OPTION] = FINISHED_STATE;
        return true;
    }

    if (hasInputJustBeenPressed(InputSystem::Input::DOWN) || hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        return true;
    }

    return false;
}

void MainScreenStateMachine::transitionStartOption()
{
    selectionTriangle->setPosition(START_SELECTION_POSITION.first, START_SELECTION_POSITION.second);
}


bool MainScreenStateMachine::onExitOption()
{
    if (hasInputJustBeenPressed(InputSystem::Input::DOWN) || hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        return true;
    }

    return false;
}

void MainScreenStateMachine::transitionExitOption()
{
    selectionTriangle->setPosition(EXIT_SELECTION_POSITION.first, EXIT_SELECTION_POSITION.second);
}
