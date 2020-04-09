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
    if (hasInputJustBeenPressed(InputSystem::Input::ACTION))
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
    if (hasInputJustBeenPressed(InputSystem::Input::ACTION))
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

    currentOption = UP;
    isReadingKey = false;

    auto up = gui.createText("bindingsScreenUp", "UP", sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8), sf::Color::Cyan);
    auto upKey = gui.createText("bindingsScreenUpKey", InputSystem::keyboardKeyToString(InputSystem::inputToKey(InputSystem::Input::UP)), sf::Vector2u(700, 300), sf::Vector2f(0.8, 0.8), sf::Color::Cyan);
    auto down = gui.createText("bindingsScreenDown", "DOWN", sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));
    auto downKey = gui.createText("bindingsScreenDownKey", InputSystem::keyboardKeyToString(InputSystem::inputToKey(InputSystem::Input::DOWN)), sf::Vector2u(700, 400), sf::Vector2f(0.8, 0.8));
    auto left = gui.createText("bindingsScreenLeft", "LEFT", sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));
    auto leftKey = gui.createText("bindingsScreenLeftKey", InputSystem::keyboardKeyToString(InputSystem::inputToKey(InputSystem::Input::LEFT)), sf::Vector2u(700, 500), sf::Vector2f(0.8, 0.8));
    auto right = gui.createText("bindingsScreenRight", "RIGHT", sf::Vector2u(320, 600), sf::Vector2f(0.8, 0.8));
    auto rightKey = gui.createText("bindingsScreenRightKey", InputSystem::keyboardKeyToString(InputSystem::inputToKey(InputSystem::Input::RIGHT)), sf::Vector2u(700, 600), sf::Vector2f(0.8, 0.8));
    auto action = gui.createText("bindingsScreenAction", "ACTION", sf::Vector2u(320, 700), sf::Vector2f(0.8, 0.8));
    auto actionKey = gui.createText("bindingsScreenActionKey", InputSystem::keyboardKeyToString(InputSystem::inputToKey(InputSystem::Input::ACTION)), sf::Vector2u(700, 700), sf::Vector2f(0.8, 0.8));
    auto exit = gui.createText("bindingsScreenExit", "EXIT", sf::Vector2u(320, 800), sf::Vector2f(0.8, 0.8));
    auto exitKey = gui.createText("bindingsScreenExitKey", InputSystem::keyboardKeyToString(InputSystem::inputToKey(InputSystem::Input::EXIT)), sf::Vector2u(700, 800), sf::Vector2f(0.8, 0.8));
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
    bool updateColor = false;
    sf::Color newColor;
    if (isReadingKey && hasInputJustBeenPressed(InputSystem::Input::EXIT))
    {
        isReadingKey = false;
        updateColor = true;
        newColor = sf::Color::Cyan;
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::EXIT))
    {
        transit<InsideConfigOptionState>();
        return;
    }
    else if (isReadingKey)
    {
        auto newKey = InputSystem::getLastKey();

        if (!InputSystem::isKeyBinded(newKey) && newKey != sf::Keyboard::Key::Unknown && newKey != lastReadKey)
        {
            const char* optionText;
            switch (currentOption)
            {
                case UP:
                    InputSystem::setInputBinding(InputSystem::Input::UP, newKey);
                    optionText = "bindingsScreenUpKey";
                    break;
                case DOWN:
                    InputSystem::setInputBinding(InputSystem::Input::DOWN, newKey);
                    optionText = "bindingsScreenDownKey";
                    break;
                case LEFT:
                    InputSystem::setInputBinding(InputSystem::Input::LEFT, newKey);
                    optionText = "bindingsScreenLeftKey";
                    break;
                case RIGHT:
                    InputSystem::setInputBinding(InputSystem::Input::RIGHT, newKey);
                    optionText = "bindingsScreenRightKey";
                    break;
                case ACTION:
                    InputSystem::setInputBinding(InputSystem::Input::ACTION, newKey);
                    optionText = "bindingsScreenActionKey";
                    break;
                case EXIT:
                    InputSystem::setInputBinding(InputSystem::Input::EXIT, newKey);
                    optionText = "bindingsScreenExitKey";
                    break;
            }

            gui.getText(optionText).lock()->setString(InputSystem::keyboardKeyToString(newKey));
            lastReadKey = newKey;
            isReadingKey = false;
            updateColor = true;
            newColor = sf::Color::Cyan;
            Config::get().write_file();
        }
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::ACTION))
    {
        isReadingKey = true;
        InputSystem::resetLastKey();
        lastReadKey = InputSystem::getLastKey();
        if (currentOption == BACK) 
        {
            transit<InsideConfigOptionState>();
            return;
        }
        updateColor = true;
        newColor = sf::Color::Green;
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::UP))
    {
        isReadingKey = false;
        updateColor = true;
        newColor = sf::Color::Cyan;
        currentOption = static_cast<CurrentOption>(((currentOption - 1) + NUM_OPTIONS) % NUM_OPTIONS);
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::DOWN))
    {
        isReadingKey = false;
        updateColor = true;
        newColor = sf::Color::Cyan;
        currentOption = static_cast<CurrentOption>((currentOption + 1) % NUM_OPTIONS);
    }

    if (updateColor)
    {
        for (const auto &optString : OPTION_STRINGS)
        {
            gui.getText(optString).lock()->setFillColor(sf::Color::White);
        }

        switch (currentOption)
        {
            case UP:
                gui.getText("bindingsScreenUp").lock()->setFillColor(newColor);
                gui.getText("bindingsScreenUpKey").lock()->setFillColor(newColor);
                break;
            case DOWN:
                gui.getText("bindingsScreenDown").lock()->setFillColor(newColor);
                gui.getText("bindingsScreenDownKey").lock()->setFillColor(newColor);
                break;
            case LEFT:
                gui.getText("bindingsScreenLeft").lock()->setFillColor(newColor);
                gui.getText("bindingsScreenLeftKey").lock()->setFillColor(newColor);
                break;
            case RIGHT:
                gui.getText("bindingsScreenRight").lock()->setFillColor(newColor);
                gui.getText("bindingsScreenRightKey").lock()->setFillColor(newColor);
                break;
            case ACTION:
                gui.getText("bindingsScreenAction").lock()->setFillColor(newColor);
                gui.getText("bindingsScreenActionKey").lock()->setFillColor(newColor);
                break;
            case EXIT:
                gui.getText("bindingsScreenExit").lock()->setFillColor(newColor);
                gui.getText("bindingsScreenExitKey").lock()->setFillColor(newColor);
                break;
            case BACK:
                gui.getText("bindingsScreenBack").lock()->setFillColor(newColor);
                break;
        }
    }
}


void BindingsOptionState::entry()
{
    gui.getText("insideConfigMainBindings").lock()->setFillColor(sf::Color::Cyan);
    gui.getText("insideConfigMainResolution").lock()->setFillColor(sf::Color::White);
    gui.getText("insideConfigMainBack").lock()->setFillColor(sf::Color::White);
}

void BindingsOptionState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::EXIT))
    {
        transit<EnterStateMainScreen>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::ACTION))
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
    current_resolution = Config::get().get_resolution();
}

void ResolutionScreenInsideState::react(const ExecuteEvent &)
{
    if (hasInputJustBeenPressed(InputSystem::Input::EXIT))
    {
        transit<InsideConfigOptionState>();
        return;
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::ACTION))
    {
        if (!isInExit)
        {
            controller.set_resolution(current_resolution);

            auto &config = Config::get();
            config.set_resolution(current_resolution);
            config.write_file();
        }
        else
        {
            transit<InsideConfigOptionState>();
            return;
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
    if (hasInputJustBeenPressed(InputSystem::Input::EXIT))
    {
        transit<EnterStateMainScreen>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::ACTION))
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
    if (hasInputJustBeenPressed(InputSystem::Input::EXIT))
    {
        transit<EnterStateMainScreen>();
    }
    else if (hasInputJustBeenPressed(InputSystem::Input::ACTION))
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
    if (hasInputJustBeenPressed(InputSystem::Input::ACTION))
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
