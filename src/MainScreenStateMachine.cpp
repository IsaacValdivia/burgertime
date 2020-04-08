#include "MainScreenStateMachine.hpp"
#include "InputSystem.hpp"

FSM_INITIAL_STATE(MainScreenStateMachine, EnterStateMainScreen)

BurgerTimeController &MainScreenStateMachine::controller = BurgerTimeController::get();
GUI &MainScreenStateMachine::gui = GUI::get();

void EnterStateMainScreen::entry()
{
    controller.clearScreen();

    auto burgerTimeText = gui.createText("enterStateMainBurTime", "BURGER TIME", sf::Vector2u(280, 150), sf::Vector2f(0.7, 0.7), sf::Color::Red);

    auto startText = gui.createText("enterStateMainStart", "START", sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));
    auto optionsText = gui.createText("enterStateMainOptions", "OPTIONS", sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));
    auto exitText = gui.createText("enterStateMainExit", "EXIT", sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));

    controller.addDrawable(burgerTimeText);
    controller.addDrawable(startText);
    controller.addDrawable(optionsText);
    controller.addDrawable(exitText);
}

void EnterStateMainScreen::react(const ExecuteEvent &)
{
    transit<StartOptionState>();
}


void StartOptionState::entry()
{
    gui.getText("enterStateMainStart").lock()->setFillColor(sf::Color::Cyan);
    gui.getText("enterStateMainOptions").lock()->setFillColor(sf::Color::White);
    gui.getText("enterStateMainExit").lock()->setFillColor(sf::Color::White);
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
        transit<ConfigOptionState>();
    }
}


void ConfigOptionState::entry()
{
    gui.getText("enterStateMainStart").lock()->setFillColor(sf::Color::White);
    gui.getText("enterStateMainOptions").lock()->setFillColor(sf::Color::Cyan);
    gui.getText("enterStateMainExit").lock()->setFillColor(sf::Color::White);
}

void ConfigOptionState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        transit<InsideConfigOptionState>();
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


void InsideConfigOptionState::entry()
{
    controller.clearScreen();

    auto bindingsText = gui.createText("insideConfigMainBindings", "BINDINGS", sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));
    auto resolutionText = gui.createText("insideConfigMainResolution", "RESOLUTION", sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));
    auto backText = gui.createText("insideConfigMainBack", "BACK", sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));

    controller.addDrawable(gui.getText("enterStateMainBurTime"));
    controller.addDrawable(bindingsText);
    controller.addDrawable(resolutionText);
    controller.addDrawable(backText);
}

void InsideConfigOptionState::react(const ExecuteEvent &)
{
    transit<BindingsOptionState>();
}


void BindingsScreenInsideState::entry()
{
    controller.clearScreen();

    auto bindings = InputSystem::getInputBindings();
    auto up = gui.createText("bindingsScreenUp", "UP", sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));
    auto upKey = gui.createText("bindingsScreenUpKey", std::string(1, bindings[InputSystem::Input::UP] + 'A'), sf::Vector2u(700, 300), sf::Vector2f(0.8, 0.8));
    auto down = gui.createText("bindingsScreenDown", "DOWN", sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));
    auto downKey = gui.createText("bindingsScreenDownKey", std::string(1, bindings[InputSystem::Input::DOWN] + 'A'), sf::Vector2u(700, 400), sf::Vector2f(0.8, 0.8));
    auto left = gui.createText("bindingsScreenLeft", "LEFT", sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));
    auto leftKey = gui.createText("bindingsScreenLeftKey", std::string(1, bindings[InputSystem::Input::LEFT] + 'A'), sf::Vector2u(700, 500), sf::Vector2f(0.8, 0.8));
    auto right = gui.createText("bindingsScreenRight", "RIGHT", sf::Vector2u(320, 600), sf::Vector2f(0.8, 0.8));
    auto rightKey = gui.createText("bindingsScreenRightKey", std::string(1, bindings[InputSystem::Input::RIGHT] + 'A'), sf::Vector2u(700, 600), sf::Vector2f(0.8, 0.8));
    auto action = gui.createText("bindingsScreenPepper", "ACTION", sf::Vector2u(320, 700), sf::Vector2f(0.8, 0.8));
    auto actionKey = gui.createText("bindingsScreenActionKey", std::string(1, bindings[InputSystem::Input::PEPPER] + 'A'), sf::Vector2u(700, 700), sf::Vector2f(0.8, 0.8));
    auto exit = gui.createText("bindingsScreenExit", "EXIT", sf::Vector2u(320, 800), sf::Vector2f(0.8, 0.8));
    auto exitKey = gui.createText("bindingsScreenExitKey", std::string(1, bindings[InputSystem::Input::PAUSE] + 'A'), sf::Vector2u(700, 800), sf::Vector2f(0.8, 0.8));
    auto back = gui.createText("bindingsScreenBack", "BACK", sf::Vector2u(320, 900), sf::Vector2f(0.8, 0.8));

    controller.addDrawable(gui.getText("enterStateMainBurTime"));
    controller.addDrawable(up);
    controller.addDrawable(upKey);
    controller.addDrawable(down);
    controller.addDrawable(downKey);
    controller.addDrawable(left);
    controller.addDrawable(leftKey);
    controller.addDrawable(right);
    controller.addDrawable(rightKey);
    controller.addDrawable(action);
    controller.addDrawable(actionKey);
    controller.addDrawable(exit);
    controller.addDrawable(exitKey);
    controller.addDrawable(back);
}

void BindingsScreenInsideState::react(const ExecuteEvent &)
{

}


void BindingsOptionState::entry()
{
    gui.getText("insideConfigMainBindings").lock()->setFillColor(sf::Color::Cyan);
    gui.getText("insideConfigMainResolution").lock()->setFillColor(sf::Color::White);
    gui.getText("insideConfigMainBack").lock()->setFillColor(sf::Color::White);
}

void BindingsOptionState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        transit<BindingsScreenInsideState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        transit<BackOptionState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::DOWN))
    {
        transit<ResolutionOptionState>();
    }
}


void ResolutionScreenInsideState::changeResolutionsText() const
{
    Config::Resolution cursor_resolution = Config::get().get_resolution();

    gui.getText("resolutionScreen250").lock()->setFillColor(sf::Color::White);
    gui.getText("resolutionScreen550").lock()->setFillColor(sf::Color::White);
    gui.getText("resolutionScreen1000").lock()->setFillColor(sf::Color::White);
    gui.getText("resolutionScreenBack").lock()->setFillColor(sf::Color::White);

    switch (cursor_resolution)
    {
        case Config::Resolution::x250x250:
            gui.getText("resolutionScreen250").lock()->setFillColor(sf::Color::Green);
            break;
        case Config::Resolution::x550x550:
            gui.getText("resolutionScreen550").lock()->setFillColor(sf::Color::Green);
            break;
        case Config::Resolution::x1000x1000:
            gui.getText("resolutionScreen1000").lock()->setFillColor(sf::Color::Green);
            break;
    }

    if (!isInExit)
    {
        switch (current_resolution)
        {
            case Config::Resolution::x250x250:
                gui.getText("resolutionScreen250").lock()->setFillColor(sf::Color::Cyan);
                break;
            case Config::Resolution::x550x550:
                gui.getText("resolutionScreen550").lock()->setFillColor(sf::Color::Cyan);
                break;
            case Config::Resolution::x1000x1000:
                gui.getText("resolutionScreen1000").lock()->setFillColor(sf::Color::Cyan);
                break;
        }
    }
    else
    {
        gui.getText("resolutionScreenBack").lock()->setFillColor(sf::Color::Cyan);
    }
}

void ResolutionScreenInsideState::entry()
{
    controller.clearScreen();

    auto res250 = gui.createText("resolutionScreen250", "250x250", sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));
    auto res550 = gui.createText("resolutionScreen550", "550x550", sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));
    auto res1000 = gui.createText("resolutionScreen1000", "1000x1000", sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));
    auto back = gui.createText("resolutionScreenBack", "BACK", sf::Vector2u(320, 600), sf::Vector2f(0.8, 0.8));

    controller.addDrawable(gui.getText("enterStateMainBurTime"));
    controller.addDrawable(res250);
    controller.addDrawable(res550);
    controller.addDrawable(res1000);
    controller.addDrawable(back);

    isInExit = false;
    current_resolution = Config::Resolution::x250x250;
}

void ResolutionScreenInsideState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        if (!isInExit)
        {
            controller.set_resolution(current_resolution);
        }
        else
        {
            transit<InsideConfigOptionState>();
        }
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        if (!isInExit)
        {
            isInExit = false;
            switch (current_resolution)
            {
                case Config::Resolution::x250x250:
                    isInExit = true;
                    break;
                case Config::Resolution::x550x550:
                    current_resolution = Config::Resolution::x250x250;
                    break;
                case Config::Resolution::x1000x1000:
                    current_resolution = Config::Resolution::x550x550;
                    break;
            }
        }
        else
        {
            isInExit = false;
            current_resolution = Config::Resolution::x1000x1000;
        }   
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::DOWN))
    {
        if (!isInExit)
        {
            isInExit = false;
            switch (current_resolution)
            {
                case Config::Resolution::x250x250:
                    current_resolution = Config::Resolution::x550x550;
                    break;
                case Config::Resolution::x550x550:
                    current_resolution = Config::Resolution::x1000x1000;
                    break;
                case Config::Resolution::x1000x1000:
                    isInExit = true;
                    break;
            }
        }
        else
        {
            isInExit = false;
            current_resolution = Config::Resolution::x250x250;
        }
    }

    changeResolutionsText();
}


void ResolutionOptionState::entry()
{
    gui.getText("insideConfigMainBindings").lock()->setFillColor(sf::Color::White);
    gui.getText("insideConfigMainResolution").lock()->setFillColor(sf::Color::Cyan);
    gui.getText("insideConfigMainBack").lock()->setFillColor(sf::Color::White);
}

void ResolutionOptionState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        transit<ResolutionScreenInsideState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        transit<BindingsOptionState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::DOWN))
    {
        transit<BackOptionState>();
    }
}


void BackOptionState::entry()
{
    gui.getText("insideConfigMainBindings").lock()->setFillColor(sf::Color::White);
    gui.getText("insideConfigMainResolution").lock()->setFillColor(sf::Color::White);
    gui.getText("insideConfigMainBack").lock()->setFillColor(sf::Color::Cyan);
}

void BackOptionState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        transit<EnterStateMainScreen>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        transit<ResolutionOptionState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::DOWN))
    {
        transit<BindingsOptionState>();
    }
}


void ExitOptionState::entry()
{
    gui.getText("enterStateMainStart").lock()->setFillColor(sf::Color::White);
    gui.getText("enterStateMainOptions").lock()->setFillColor(sf::Color::White);
    gui.getText("enterStateMainExit").lock()->setFillColor(sf::Color::Cyan);
}

void ExitOptionState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::PEPPER))
    {
        transit<FinishedExitState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        transit<ConfigOptionState>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::DOWN))
    {
        transit<StartOptionState>();
    }
}
