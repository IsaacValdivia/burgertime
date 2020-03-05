#include "MainScreenStateMachine.hpp"

#include "BurgerTimeStateMachine.hpp"
#include "BurgerTimeController.hpp"
#include "InputSystem.hpp"


MainScreenStateMachine::MainScreenStateMachine() 
: StateMachine(INITIAL_STATE), controller(BurgerTimeController::get())
{}

std::pair<bool, uint32_t> MainScreenStateMachine::nextOnStateLogic()
{
    return onStateLogic[currentState]();
}

void MainScreenStateMachine::nextTransitionStateLogic()
{
    transitionStateLogic[currentState]();
}

std::pair<bool, uint32_t> MainScreenStateMachine::mainStateMachineBinding()
{
    execute();

    switch (currentState)
    {
        case FINISHED_EXIT_STATE:
            // TODO: change to BurgerTimeStateMachine::State::EXIT_GAME or sth like that
            return std::make_pair(true, BurgerTimeStateMachine::State::GAME_READY_SCREEN);
        
        case FINISHED_START_STATE:
            return std::make_pair(true, BurgerTimeStateMachine::State::GAME_READY_SCREEN);

        default:
            return std::make_pair(false, BurgerTimeStateMachine::State::GAME_READY_SCREEN);
    }
}


std::pair<bool, MainScreenStateMachine::State> MainScreenStateMachine::onEntered()
{
    return std::make_pair(true, START_OPTION);
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
}


std::pair<bool, MainScreenStateMachine::State> MainScreenStateMachine::onFinished()
{
    return std::make_pair(false, ENTER_STATE);
}


void MainScreenStateMachine::transitionFinished()
{

}


std::pair<bool, MainScreenStateMachine::State> MainScreenStateMachine::onStartOption()
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        return std::make_pair(true, FINISHED_START_STATE);
    }

    if (hasInputJustBeenPressed(InputSystem::Input::DOWN) || hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        return std::make_pair(true, EXIT_OPTION);
    }

    return std::make_pair(false, EXIT_OPTION);
}

void MainScreenStateMachine::transitionStartOption()
{
    selectionTriangle->setPosition(START_SELECTION_POSITION.first, START_SELECTION_POSITION.second);
}


std::pair<bool, MainScreenStateMachine::State> MainScreenStateMachine::onExitOption()
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        return std::make_pair(true, FINISHED_EXIT_STATE);
    }

    if (hasInputJustBeenPressed(InputSystem::Input::DOWN) || hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        return std::make_pair(true, START_OPTION);
    }

    return std::make_pair(false, START_OPTION);
}

void MainScreenStateMachine::transitionExitOption()
{
    selectionTriangle->setPosition(EXIT_SELECTION_POSITION.first, EXIT_SELECTION_POSITION.second);
}
