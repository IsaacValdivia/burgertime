#include "MainScreenStateMachine.hpp"

#include "InputSystem.hpp"

FSM_INITIAL_STATE(MainScreenStateMachine, EnterStateMainScreen)

BurgerTimeController &MainScreenStateMachine::controller = BurgerTimeController::get();

GUI &MainScreenStateMachine::gui = GUI::get();

std::shared_ptr<sf::CircleShape> MainScreenStateMachine::selection_triangle = nullptr;

void EnterStateMainScreen::entry() {
    controller.clear_screen();

    auto burger_time_text = gui.create_text("enterStateMainBurTime", "BURGER TIME",
                                            sf::Vector2u(280, 150),
                                            sf::Vector2f(0.7, 0.7),
                                            sf::Color::Red);

    auto start_text = gui.create_text("enterStateMainStart", "START",
                                      sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));

    auto options_text = gui.create_text("enterStateMainOptions", "OPTIONS",
                                        sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));

    auto exit_text = gui.create_text("enterStateMainExit", "EXIT",
                                     sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));

    selection_triangle = std::make_shared<sf::CircleShape>(10, 3);
    selection_triangle->setFillColor(sf::Color::White);
    selection_triangle->setRotation(90);

    controller.add_drawable(burger_time_text);
    controller.add_drawable(start_text);
    controller.add_drawable(options_text);
    controller.add_drawable(exit_text);
    controller.add_drawable(selection_triangle);
}

void EnterStateMainScreen::react(const ExecuteEvent &) {
    transit<StartOptionState>();
}

void StartOptionState::entry() {
    selection_triangle->setPosition(START_SELECTION_POSITION.first,
                                    START_SELECTION_POSITION.second);
}

void StartOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::PEPPER)) {
        transit<FinishedStartState>();
        Audio::play(Audio::Track::COIN_INSERTED);
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<ExitOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<BindingsOptionState>();
    }
}


void BindingsOptionState::entry() {
    selection_triangle->setPosition(BINDINGS_SELECTION_POSITION.first,
                                    BINDINGS_SELECTION_POSITION.second);
}

void BindingsOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::PEPPER)) {
        // TODO
        // transit<FinishedExitState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<StartOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<ExitOptionState>();
    }
}


void ExitOptionState::entry() {
    selection_triangle->setPosition(EXIT_SELECTION_POSITION.first,
                                    EXIT_SELECTION_POSITION.second);
}

void ExitOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::PEPPER)) {
        transit<FinishedExitState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP)) {
        transit<BindingsOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN)) {
        transit<StartOptionState>();
    }
}
