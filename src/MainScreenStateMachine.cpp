#include "MainScreenStateMachine.hpp"
#include "InputSystem.hpp"

FSM_INITIAL_STATE(MainScreenStateMachine, EnterStateMainScreen)

BurgerTimeController &MainScreenStateMachine::controller = BurgerTimeController::get();
GUI &MainScreenStateMachine::gui = GUI::get();
std::shared_ptr<sf::CircleShape> MainScreenStateMachine::selectionTriangle = nullptr;

void EnterStateMainScreen::entry()
{
    controller.clearScreen();

    auto burgerTimeText = gui.createText("enterStateMainBurTime", "BURGER TIME", sf::Vector2u(280, 150), sf::Vector2f(0.7, 0.7), sf::Color::Red);

    auto startText = gui.createText("enterStateMainStart", "START", sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));

    auto optionsText = gui.createText("enterStateMainOptions", "OPTIONS", sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));

    auto exitText = gui.createText("enterStateMainExit", "EXIT", sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));

    selectionTriangle = std::make_shared<sf::CircleShape>(10, 3);
    selectionTriangle->setFillColor(sf::Color::White);
    selectionTriangle->setRotation(90);

    controller.addDrawable(burgerTimeText);
    controller.addDrawable(startText);
    controller.addDrawable(optionsText);
    controller.addDrawable(exitText);
    controller.addDrawable(selectionTriangle);
}

void EnterStateMainScreen::react(const ExecuteEvent &)
{
    transit<StartOptionState>();
}



void StartOptionState::entry()
{
    selectionTriangle->setPosition(START_SELECTION_POSITION.first, START_SELECTION_POSITION.second);
}

void StartOptionState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        transit<FinishedStartState>();
        Audio::play(Audio::Track::COIN_INSERTED);
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


void BindingsOptionState::entry()
{
    selectionTriangle->setPosition(BINDINGS_SELECTION_POSITION.first, BINDINGS_SELECTION_POSITION.second);
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


void ExitOptionState::entry()
{
    selectionTriangle->setPosition(EXIT_SELECTION_POSITION.first, EXIT_SELECTION_POSITION.second);
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
