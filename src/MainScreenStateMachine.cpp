#include "MainScreenStateMachine.hpp"
#include "InputSystem.hpp"

FSM_INITIAL_STATE(MainScreenStateMachine, EnterStateMainScreen)

BurgerTimeController &MainScreenStateMachine::controller = BurgerTimeController::get();
std::shared_ptr<sf::CircleShape> MainScreenStateMachine::selectionTriangle = nullptr;

void MainScreenStateMachine::enterStateEntry()
{
    controller.drawablesOnScreen.clear();

    auto burgerTimeText = std::make_shared<sf::Text>();
    burgerTimeText->setFillColor(sf::Color::Red);
    burgerTimeText->setScale(0.70, 0.70);
    burgerTimeText->setFont(controller.font);
    burgerTimeText->setString("BURGER TIME");
    burgerTimeText->setPosition(32 * WINDOW_WIDTH / 100, 15 * WINDOW_HEIGHT / 100);

    auto startText = std::make_shared<sf::Text>();
    startText->setFont(controller.font);
    startText->setString("START");
    startText->setScale(0.8, 0.8);
    startText->setPosition(4 * WINDOW_WIDTH / 10, 3 * WINDOW_HEIGHT / 10);

    auto bindingsText = std::make_shared<sf::Text>();
    bindingsText->setFont(controller.font);
    bindingsText->setString("BINDINGS");
    bindingsText->setScale(0.8, 0.8);
    bindingsText->setPosition(4 * WINDOW_WIDTH / 10, 4 * WINDOW_HEIGHT / 10);

    auto exitText = std::make_shared<sf::Text>();
    exitText->setFont(controller.font);
    exitText->setString("EXIT");
    exitText->setScale(0.8, 0.8);
    exitText->setPosition(4 * WINDOW_WIDTH / 10, 5 * WINDOW_HEIGHT / 10);

    selectionTriangle = std::make_shared<sf::CircleShape>(10, 3);
    selectionTriangle->setFillColor(sf::Color::White);
    selectionTriangle->setRotation(90);

    controller.drawablesOnScreen.push_back(burgerTimeText);
    controller.drawablesOnScreen.push_back(startText);
    controller.drawablesOnScreen.push_back(bindingsText);
    controller.drawablesOnScreen.push_back(exitText);
    controller.drawablesOnScreen.push_back(selectionTriangle);
}

void EnterStateMainScreen::entry()
{
    MainScreenStateMachine::enterStateEntry();
}

void EnterStateMainScreen::react(const ExecuteEvent &)
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
    else if (hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        transit<ExitOptionState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::DOWN))
    {
        transit<BindingsOptionState>();
    }
}


void MainScreenStateMachine::bindingsOptionStateEntry()
{
    selectionTriangle->setPosition(BINDINGS_SELECTION_POSITION.first, BINDINGS_SELECTION_POSITION.second);
}

void BindingsOptionState::entry()
{
    MainScreenStateMachine::bindingsOptionStateEntry();
}

void BindingsOptionState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        // TODO
        // transit<FinishedExitState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        transit<StartOptionState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::DOWN))
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
    else if (hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        transit<BindingsOptionState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::DOWN))
    {
        transit<StartOptionState>();
    }
}
