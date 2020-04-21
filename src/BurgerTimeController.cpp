#include "BurgerTimeController.hpp"

#include "Constants.hpp"
#include "InputSystem.hpp"
#include "Audio.hpp"
#include "BurgerTimeStateMachine.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <SFML/System.hpp>
#include <ctime>

BurgerTimeController::BurgerTimeController() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE,
           sf::Style::Titlebar | sf::Style::Close) {}

BurgerTimeController::~BurgerTimeController() {}

void BurgerTimeController::clear_screen() {
    drawables_on_screen.clear();
}

void BurgerTimeController::add_drawable(std::weak_ptr<sf::Drawable> new_drawable) {
    drawables_on_screen.push_back(new_drawable);
}

void BurgerTimeController::restart_timer() {
    logic_clock.restart();
}

void BurgerTimeController::pause_timer() {
    logic_clock.pause();
}

void BurgerTimeController::start_timer() {
    logic_clock.start();
}

sf::Time BurgerTimeController::get_elapsed_time() {
    return logic_clock.getElapsedTime();
}


Difficulty BurgerTimeController::get_selected_difficulty() const {
    return selected_difficulty;
}

void BurgerTimeController::set_difficulty(Difficulty new_difficulty) {
    selected_difficulty = new_difficulty;
}

BurgerTimeController &BurgerTimeController::get() {
    static BurgerTimeController instance;
    return instance;
}

void BurgerTimeController::startup() {
    // No borrar, al ser singletons se tienen que inicializar cuanto antes
    GUI::get();
    Config::get();

    srand(time(NULL));

    BurgerTimeStateMachine::start();
    window.setKeyRepeatEnabled(false);
    Audio::init();
    restart_timer();
}

void BurgerTimeController::run() {
    startup();

    const auto LOGIC_DELTA_TIME = sf::seconds(LOGIC_UPDATE_FREQ);

    sf::Clock clock;
    auto next_time = clock.getElapsedTime();
    auto last_time = clock.getElapsedTime();

    const auto MAX_TIME_DIFF = sf::seconds(0.5);
    constexpr int MAX_SKIPPED_FRAMES = 5;
    int skipped_frames = 1;

    while (window.isOpen() && !has_game_finished()) {
        auto current_time = clock.getElapsedTime();

        if (current_time - next_time > MAX_TIME_DIFF) {
            next_time = current_time;
        }

        if (current_time >= next_time) {
            float frame_time = (current_time - last_time).asSeconds();
            last_time = current_time;

            next_time += LOGIC_DELTA_TIME;

            while (frame_time > 0.0) {
                float delta_t = std::min(frame_time, LOGIC_UPDATE_FREQ);
                update(delta_t);
                frame_time -= delta_t;
            }

            if ((current_time < next_time) || (skipped_frames > MAX_SKIPPED_FRAMES)) {
                draw();
                skipped_frames = 1;
            }
            else {
                skipped_frames++;
            }
        }
        else {
            auto sleep_time = next_time - current_time;

            std::chrono::microseconds sleep_time_micro(sleep_time.asMicroseconds());
            if (sleep_time_micro.count() > 0) {
                std::this_thread::sleep_for(sleep_time_micro);
            }
        }
    }
}

void BurgerTimeController::update(float delta_t) {
    sf::Event event;

    bool is_text_entered = false;
    char char_entered;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::TextEntered) {
            if ((event.text.unicode >= 'a' && event.text.unicode <= 'z') ||
                    (event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||
                    (event.text.unicode >= '0' && event.text.unicode <= '9')) {
                char_entered = static_cast<char>(event.text.unicode);
                is_text_entered = true;
            }
        }
        else if (event.type == sf::Event::KeyPressed) {
            InputSystem::update_last_key(event.key.code);

        }
    }

    if (is_text_entered) {
        InputSystem::update(char_entered);
        is_text_entered = false;
    }
    else {
        InputSystem::update();
    }

    BurgerTimeStateMachine::dispatch(ExecuteEvent(delta_t));
}

void BurgerTimeController::draw() {
    window.clear();

    for (auto obj_weak_it = drawables_on_screen.begin(); obj_weak_it
            != drawables_on_screen.end(); ++obj_weak_it) {

        if (auto obj = obj_weak_it->lock()) {
            window.draw(*obj);
        }
        else {
            obj_weak_it = drawables_on_screen.erase(obj_weak_it);
            --obj_weak_it;
        }
    }

    window.display();
}

bool BurgerTimeController::has_game_finished() const {
    return BurgerTimeStateMachine::is_in_state<FinishedState>();
}

void BurgerTimeController::set_resolution(Config::Resolution new_resolution) {
    sf::Vector2u resolutionSize;
    switch (new_resolution) {
        case Config::Resolution::x250x250:
            resolutionSize.x = 250;
            resolutionSize.y = 250;
            break;
        case Config::Resolution::x550x550:
            resolutionSize.x = 550;
            resolutionSize.y = 550;
            break;
        case Config::Resolution::x1000x1000:
            resolutionSize.x = 1000;
            resolutionSize.y = 1000;
            break;
    }
    window.setSize(resolutionSize);
}