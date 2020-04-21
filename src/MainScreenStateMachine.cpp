#include "MainScreenStateMachine.hpp"

#include "InputSystem.hpp"

FSM_INITIAL_STATE(MainScreenStateMachine, EnterStateMainScreen)

BurgerTimeController &MainScreenStateMachine::controller = BurgerTimeController::get();
GUI &MainScreenStateMachine::gui = GUI::get();

void EnterStateMainScreen::entry() {
    controller.clear_screen();

    auto burger_time_text = gui.create_text("enterStateMainBurTime", "BURGER TIME",
                                            sf::Vector2u(280, 150), sf::Vector2f(0.7, 0.7),
                                            sf::Color::Red);

    auto start_text = gui.create_text("enterStateMainStart", "START",
                                      sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));
    auto options_text = gui.create_text("enterStateMainOptions", "OPTIONS",
                                        sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));
    auto exit_text = gui.create_text("enterStateMainExit", "EXIT",
                                     sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));

    controller.add_drawable(burger_time_text);
    controller.add_drawable(start_text);
    controller.add_drawable(options_text);
    controller.add_drawable(exit_text);
}

void EnterStateMainScreen::react(const ExecuteEvent &) {
    transit<StartOptionState>();
}

void StartOptionState::entry() {
    gui.get_text("enterStateMainStart").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("enterStateMainOptions").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainExit").lock()->setFillColor(sf::Color::White);
}

void StartOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::ACTION)) {
        transit<DifficultyScreenEnterState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<ExitOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<ConfigOptionState>();
    }
}

void ConfigOptionState::entry() {
    gui.get_text("enterStateMainStart").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainOptions").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("enterStateMainExit").lock()->setFillColor(sf::Color::White);
}

void ConfigOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::ACTION)) {
        transit<InsideConfigOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<StartOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<ExitOptionState>();
    }
}

void InsideConfigOptionState::entry() {
    controller.clear_screen();

    auto bindings_text = gui.create_text("insideConfigMainBindings", "CONTROLS",
                                         sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));

    auto resolution_text = gui.create_text("insideConfigMainResolution", "RESOLUTION",
                                           sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));

    auto back_text = gui.create_text("insideConfigMainBack", "BACK", sf::Vector2u(320, 500),
                                     sf::Vector2f(0.8, 0.8));

    controller.add_drawable(gui.get_text("enterStateMainBurTime"));
    controller.add_drawable(bindings_text);
    controller.add_drawable(resolution_text);
    controller.add_drawable(back_text);
}

void InsideConfigOptionState::react(const ExecuteEvent &) {
    transit<BindingsOptionState>();
}


void BindingsScreenInsideState::entry() {
    controller.clear_screen();

    current_option = UP;
    is_reading_key = false;

    auto up = gui.create_text("bindingsScreenUp", "UP", sf::Vector2u(320, 300),
                              sf::Vector2f(0.8, 0.8), sf::Color::Cyan);

    auto up_key = gui.create_text("bindingsScreenUpKey",
                                  InputSystem::keyboard_key_to_string(
                                      InputSystem::input_to_key(
                                          InputSystem::Input::UP)),
                                  sf::Vector2u(700, 300),
                                  sf::Vector2f(0.8, 0.8),
                                  sf::Color::Cyan);

    auto down = gui.create_text("bindingsScreenDown", "DOWN",
                                sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));

    auto down_key = gui.create_text("bindingsScreenDownKey",
                                    InputSystem::keyboard_key_to_string(
                                        InputSystem::input_to_key(
                                            InputSystem::Input::DOWN)),
                                    sf::Vector2u(700, 400),
                                    sf::Vector2f(0.8, 0.8));

    auto left = gui.create_text("bindingsScreenLeft", "LEFT",
                                sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));
    auto left_key = gui.create_text("bindingsScreenLeftKey",
                                    InputSystem::keyboard_key_to_string(
                                        InputSystem::input_to_key(
                                            InputSystem::Input::LEFT)),
                                    sf::Vector2u(700, 500),
                                    sf::Vector2f(0.8, 0.8));

    auto right = gui.create_text("bindingsScreenRight", "RIGHT",
                                 sf::Vector2u(320, 600), sf::Vector2f(0.8, 0.8));

    auto right_key = gui.create_text("bindingsScreenRightKey",
                                     InputSystem::keyboard_key_to_string(
                                         InputSystem::input_to_key(
                                                 InputSystem::Input::RIGHT)),
                                     sf::Vector2u(700, 600),
                                     sf::Vector2f(0.8, 0.8));

    auto action = gui.create_text("bindingsScreenAction", "ACTION",
                                  sf::Vector2u(320, 700), sf::Vector2f(0.8, 0.8));
    auto action_key = gui.create_text("bindingsScreenActionKey",
                                      InputSystem::keyboard_key_to_string(
                                          InputSystem::input_to_key(
                                                  InputSystem::Input::ACTION)),
                                      sf::Vector2u(700, 700), sf::Vector2f(0.8, 0.8));

    auto exit = gui.create_text("bindingsScreenExit", "EXIT",
                                sf::Vector2u(320, 800), sf::Vector2f(0.8, 0.8));

    auto exit_key = gui.create_text("bindingsScreenExitKey",
                                    InputSystem::keyboard_key_to_string(
                                        InputSystem::input_to_key(InputSystem::Input::EXIT)),
                                    sf::Vector2u(700, 800), sf::Vector2f(0.8, 0.8));

    auto back = gui.create_text("bindingsScreenBack", "BACK",
                                sf::Vector2u(320, 900), sf::Vector2f(0.8, 0.8));

    controller.add_drawable(gui.get_text("enterStateMainBurTime"));
    controller.add_drawable(up);
    controller.add_drawable(up_key);
    controller.add_drawable(down);
    controller.add_drawable(down_key);
    controller.add_drawable(left);
    controller.add_drawable(left_key);
    controller.add_drawable(right);
    controller.add_drawable(right_key);
    controller.add_drawable(action);
    controller.add_drawable(action_key);
    controller.add_drawable(exit);
    controller.add_drawable(exit_key);
    controller.add_drawable(back);
}

void BindingsScreenInsideState::react(const ExecuteEvent &) {
    bool update_color = false;
    sf::Color new_color;
    if (is_reading_key && has_input_just_been_pressed(InputSystem::Input::EXIT)) {
        is_reading_key = false;
        update_color = true;
        new_color = sf::Color::Cyan;
    }
    else if (has_input_just_been_pressed(InputSystem::Input::EXIT)) {
        transit<InsideConfigOptionState>();
        return;
    }
    else if (is_reading_key) {
        auto new_key = InputSystem::get_last_key();

        if (!InputSystem::is_key_binded(new_key) &&
                new_key != sf::Keyboard::Key::Unknown && new_key != last_read_key) {

            const char *option_text;
            switch (current_option) {
                case UP:
                    InputSystem::set_input_binding(InputSystem::Input::UP, new_key);
                    option_text = "bindingsScreenUpKey";
                    break;
                case DOWN:
                    InputSystem::set_input_binding(InputSystem::Input::DOWN, new_key);
                    option_text = "bindingsScreenDownKey";
                    break;
                case LEFT:
                    InputSystem::set_input_binding(InputSystem::Input::LEFT, new_key);
                    option_text = "bindingsScreenLeftKey";
                    break;
                case RIGHT:
                    InputSystem::set_input_binding(InputSystem::Input::RIGHT, new_key);
                    option_text = "bindingsScreenRightKey";
                    break;
                case ACTION:
                    InputSystem::set_input_binding(InputSystem::Input::ACTION, new_key);
                    option_text = "bindingsScreenActionKey";
                    break;
                case EXIT:
                    InputSystem::set_input_binding(InputSystem::Input::EXIT, new_key);
                    option_text = "bindingsScreenExitKey";
                    break;
            }

            gui.get_text(option_text).lock()->setString(
                InputSystem::keyboard_key_to_string(new_key));

            last_read_key = new_key;
            is_reading_key = false;
            update_color = true;
            new_color = sf::Color::Cyan;
            Config::get().write_file();
        }
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ACTION)) {
        is_reading_key = true;
        InputSystem::reset_last_key();
        last_read_key = InputSystem::get_last_key();
        if (current_option == BACK) {
            transit<InsideConfigOptionState>();
            return;
        }
        update_color = true;
        new_color = sf::Color::Green;
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        is_reading_key = false;
        update_color = true;
        new_color = sf::Color::Cyan;
        current_option = static_cast<CurrentOption>(((current_option - 1)
                         + NUM_OPTIONS) % NUM_OPTIONS);
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        is_reading_key = false;
        update_color = true;
        new_color = sf::Color::Cyan;
        current_option = static_cast<CurrentOption>((current_option + 1) %
                         NUM_OPTIONS);
    }

    if (update_color) {
        for (const auto &optString : OPTION_STRINGS) {
            gui.get_text(optString).lock()->setFillColor(sf::Color::White);
        }

        switch (current_option) {
            case UP:
                gui.get_text("bindingsScreenUp").lock()->setFillColor(new_color);
                gui.get_text("bindingsScreenUpKey").lock()->setFillColor(new_color);
                break;
            case DOWN:
                gui.get_text("bindingsScreenDown").lock()->setFillColor(new_color);
                gui.get_text("bindingsScreenDownKey").lock()->setFillColor(new_color);
                break;
            case LEFT:
                gui.get_text("bindingsScreenLeft").lock()->setFillColor(new_color);
                gui.get_text("bindingsScreenLeftKey").lock()->setFillColor(new_color);
                break;
            case RIGHT:
                gui.get_text("bindingsScreenRight").lock()->setFillColor(new_color);
                gui.get_text("bindingsScreenRightKey").lock()->setFillColor(new_color);
                break;
            case ACTION:
                gui.get_text("bindingsScreenAction").lock()->setFillColor(new_color);
                gui.get_text("bindingsScreenActionKey").lock()->setFillColor(new_color);
                break;
            case EXIT:
                gui.get_text("bindingsScreenExit").lock()->setFillColor(new_color);
                gui.get_text("bindingsScreenExitKey").lock()->setFillColor(new_color);
                break;
            case BACK:
                gui.get_text("bindingsScreenBack").lock()->setFillColor(new_color);
                break;
        }
    }
}


void BindingsOptionState::entry() {
    gui.get_text("insideConfigMainBindings").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("insideConfigMainResolution").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainBack").lock()->setFillColor(sf::Color::White);
}

void BindingsOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::EXIT)) {
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ACTION)) {
        transit<BindingsScreenInsideState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<BackOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<ResolutionOptionState>();
    }
}


void ResolutionScreenInsideState::change_resolutions_text() const {
    Config::Resolution cursor_resolution = Config::get().get_resolution();

    gui.get_text("resolutionScreen250").lock()->setFillColor(sf::Color::White);
    gui.get_text("resolutionScreen550").lock()->setFillColor(sf::Color::White);
    gui.get_text("resolutionScreen1000").lock()->setFillColor(sf::Color::White);
    gui.get_text("resolutionScreenBack").lock()->setFillColor(sf::Color::White);

    switch (cursor_resolution) {
        case Config::Resolution::x250x250:
            gui.get_text("resolutionScreen250").lock()->setFillColor(sf::Color::Green);
            break;
        case Config::Resolution::x550x550:
            gui.get_text("resolutionScreen550").lock()->setFillColor(sf::Color::Green);
            break;
        case Config::Resolution::x1000x1000:
            gui.get_text("resolutionScreen1000").lock()->setFillColor(sf::Color::Green);
            break;
    }

    if (!is_in_exit) {
        switch (current_resolution) {
            case Config::Resolution::x250x250:
                gui.get_text("resolutionScreen250").lock()->setFillColor(sf::Color::Cyan);
                break;
            case Config::Resolution::x550x550:
                gui.get_text("resolutionScreen550").lock()->setFillColor(sf::Color::Cyan);
                break;
            case Config::Resolution::x1000x1000:
                gui.get_text("resolutionScreen1000").lock()->setFillColor(sf::Color::Cyan);
                break;
        }
    }
    else {
        gui.get_text("resolutionScreenBack").lock()->setFillColor(sf::Color::Cyan);
    }
}

void ResolutionScreenInsideState::entry() {
    controller.clear_screen();

    auto res250 = gui.create_text("resolutionScreen250", "250x250",
                                  sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));
    auto res550 = gui.create_text("resolutionScreen550", "550x550",
                                  sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));
    auto res1000 = gui.create_text("resolutionScreen1000", "1000x1000",
                                   sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));
    auto back = gui.create_text("resolutionScreenBack", "BACK",
                                sf::Vector2u(320, 600), sf::Vector2f(0.8, 0.8));

    controller.add_drawable(gui.get_text("enterStateMainBurTime"));
    controller.add_drawable(res250);
    controller.add_drawable(res550);
    controller.add_drawable(res1000);
    controller.add_drawable(back);

    is_in_exit = false;
    current_resolution = Config::get().get_resolution();
}

void ResolutionScreenInsideState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::EXIT)) {
        transit<InsideConfigOptionState>();
        return;
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ACTION)) {
        if (!is_in_exit) {
            controller.set_resolution(current_resolution);

            auto &config = Config::get();
            config.set_resolution(current_resolution);
            config.write_file();
        }
        else {
            transit<InsideConfigOptionState>();
            return;
        }
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        if (!is_in_exit) {
            is_in_exit = false;
            switch (current_resolution) {
                case Config::Resolution::x250x250:
                    is_in_exit = true;
                    break;
                case Config::Resolution::x550x550:
                    current_resolution = Config::Resolution::x250x250;
                    break;
                case Config::Resolution::x1000x1000:
                    current_resolution = Config::Resolution::x550x550;
                    break;
            }
        }
        else {
            is_in_exit = false;
            current_resolution = Config::Resolution::x1000x1000;
        }
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        if (!is_in_exit) {
            is_in_exit = false;
            switch (current_resolution) {
                case Config::Resolution::x250x250:
                    current_resolution = Config::Resolution::x550x550;
                    break;
                case Config::Resolution::x550x550:
                    current_resolution = Config::Resolution::x1000x1000;
                    break;
                case Config::Resolution::x1000x1000:
                    is_in_exit = true;
                    break;
            }
        }
        else {
            is_in_exit = false;
            current_resolution = Config::Resolution::x250x250;
        }
    }

    change_resolutions_text();
}


void ResolutionOptionState::entry() {
    gui.get_text("insideConfigMainBindings").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainResolution").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("insideConfigMainBack").lock()->setFillColor(sf::Color::White);
}

void ResolutionOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::EXIT)) {
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ACTION)) {
        transit<ResolutionScreenInsideState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<BindingsOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<BackOptionState>();
    }
}


void BackOptionState::entry() {
    gui.get_text("insideConfigMainBindings").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainResolution").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainBack").lock()->setFillColor(sf::Color::Cyan);
}

void BackOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::EXIT)) {
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ACTION)) {
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<ResolutionOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<BindingsOptionState>();
    }
}


void ExitOptionState::entry() {
    gui.get_text("enterStateMainStart").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainOptions").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainExit").lock()->setFillColor(sf::Color::Cyan);
}

void ExitOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::ACTION)) {
        transit<FinishedExitState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<ConfigOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<StartOptionState>();
    }
}


void DifficultyScreenEnterState::entry() {
    controller.clear_screen();

    auto classic_text = gui.create_text("difficultyStateClassic", "CLASSIC",
                                      sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));
    auto hard_text = gui.create_text("difficultyStateHard", "HARD",
                                        sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));
    auto smiley_text = gui.create_text("difficultyStateSmiley", ":-)",
                                     sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));

    controller.add_drawable(gui.get_text("enterStateMainBurTime"));
    controller.add_drawable(classic_text);
    controller.add_drawable(hard_text);
    controller.add_drawable(smiley_text);
}

void DifficultyScreenEnterState::react(const ExecuteEvent &) {
    transit<DifficultyScreenClassicState>();
}


void DifficultyScreenClassicState::entry() {
    gui.get_text("difficultyStateClassic").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("difficultyStateHard").lock()->setFillColor(sf::Color::White);
    gui.get_text("difficultyStateSmiley").lock()->setFillColor(sf::Color::White);
}

void DifficultyScreenClassicState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::EXIT)) {
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ACTION)) {
        controller.set_difficulty(CLASSIC);
        transit<FinishedStartState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<DifficultyScreenSmileyState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<DifficultyScreenHardState>();
    }
}


void DifficultyScreenHardState::entry() {
    gui.get_text("difficultyStateClassic").lock()->setFillColor(sf::Color::White);
    gui.get_text("difficultyStateHard").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("difficultyStateSmiley").lock()->setFillColor(sf::Color::White);
}

void DifficultyScreenHardState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::EXIT)) {
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ACTION)) {
        controller.set_difficulty(HARD);
        transit<FinishedStartState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<DifficultyScreenClassicState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<DifficultyScreenSmileyState>();
    }
}


void DifficultyScreenSmileyState::entry() {
    gui.get_text("difficultyStateClassic").lock()->setFillColor(sf::Color::White);
    gui.get_text("difficultyStateHard").lock()->setFillColor(sf::Color::White);
    gui.get_text("difficultyStateSmiley").lock()->setFillColor(sf::Color::Cyan);
}

void DifficultyScreenSmileyState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::EXIT)) {
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ACTION)) {
        controller.set_difficulty(SMILEY);
        transit<FinishedStartState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<DifficultyScreenHardState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<DifficultyScreenClassicState>();
    }
}
