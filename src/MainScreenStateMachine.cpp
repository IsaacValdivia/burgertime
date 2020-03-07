#include "MainScreenStateMachine.hpp"
#include "InputSystem.hpp"

FSM_INITIAL_STATE(MainScreenStateMachine, EnterState)

BurgerTimeController &MainScreenStateMachine::controller = BurgerTimeController::get();
std::shared_ptr<sf::CircleShape> MainScreenStateMachine::selectionTriangle = nullptr;

void MainScreenStateMachine::enterStateEntry()
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
    // selectionTriangle->setPosition(START_SELECTION_POSITION.first, START_SELECTION_POSITION.second);

    controller.drawablesOnScreen.push_back(startText);
    controller.drawablesOnScreen.push_back(exitText);
    controller.drawablesOnScreen.push_back(selectionTriangle);
}

void EnterState::entry()
{
    MainScreenStateMachine::enterStateEntry();
}

void EnterState::react(const ExecuteEvent &)
{
    transit<StartOptionState>();
}


void MainScreenStateMachine::startOptionStateEntry()
{
    selectionTriangle->setPosition(START_SELECTION_POSITION.first, START_SELECTION_POSITION.second);
}

void StartOptionState::entry()
{
    MainScreenStateMachine::startOptionStateEntry();
}

void StartOptionState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        transit<FinishedStartState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::DOWN) || hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        transit<ExitOptionState>();
    }
}


void MainScreenStateMachine::exitOptionStateEntry()
{
    selectionTriangle->setPosition(EXIT_SELECTION_POSITION.first, EXIT_SELECTION_POSITION.second);
}

void ExitOptionState::entry()
{
    MainScreenStateMachine::exitOptionStateEntry();
}

void ExitOptionState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        transit<FinishedExitState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::DOWN) || hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        transit<StartOptionState>();
    }
}
