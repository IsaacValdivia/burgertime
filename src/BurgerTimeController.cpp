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
           sf::Style::Titlebar | sf::Style::Close) {
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    auto best_bpp = modes[0].bitsPerPixel;
    for (std::size_t i = 0; i < modes.size(); ++i) {
        sf::VideoMode mode = modes[i];
        if (mode.bitsPerPixel != best_bpp) {
            break;
        }

        available_resolutions.push_back(sf::Vector2u(mode.width, mode.height));
    }
    std::reverse(available_resolutions.begin(), available_resolutions.end());
    // window(sf::VideoMode::getDesktopMode(), WINDOW_TITLE, sf::Style::None) {}

    letter_view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    letter_view.setCenter(letter_view.getSize().x / 2, letter_view.getSize().y / 2);
    set_letterbox_view(WINDOW_WIDTH, WINDOW_HEIGHT);
}


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
    Audio::init();
    Config::get();
    
    window_borderless_switch();

    srand(time(NULL));

    BurgerTimeStateMachine::start();
    window.setKeyRepeatEnabled(false);
    restart_timer();
}

void BurgerTimeController::run() {
    startup();

    Audio::play(Audio::MusicTrack::MENU_MUSIC);

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
        else if (event.type == sf::Event::KeyPressed && is_in_focus) {
            InputSystem::update_last_key(event.key.code);
        }
        else if (event.type == sf::Event::GainedFocus) {
            is_in_focus = true;
        }
        else if (event.type == sf::Event::LostFocus) {
            is_in_focus = false;
        }
    }

    if (is_in_focus) {
        if (is_text_entered) {
            InputSystem::update(char_entered);
            is_text_entered = false;
        }
        else {
            InputSystem::update();
        }
    }

    BurgerTimeStateMachine::dispatch(ExecuteEvent(delta_t));
}

void BurgerTimeController::draw() {
    window.clear();
    window.setView(letter_view);

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

void BurgerTimeController::window_borderless_switch() {
    auto resolution = Config::get().get_resolution();
    auto video_mode = sf::VideoMode(resolution.x, resolution.y);
    if (Config::get().get_are_borders_on()) {
        window.create(video_mode, WINDOW_TITLE,
            sf::Style::Titlebar | sf::Style::Close);
    }
    else {
        window.create(video_mode, WINDOW_TITLE,
           sf::Style::None);
    }

    sf::Image window_icon;
    window_icon.loadFromFile("img/window_icon.png");
    window.setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());
}

bool BurgerTimeController::has_game_finished() const {
    return BurgerTimeStateMachine::is_in_state<FinishedState>();
}

void BurgerTimeController::set_resolution(sf::Vector2u new_resolution) {
    set_letterbox_view(new_resolution.x, new_resolution.y);
    window.setSize(new_resolution);
}

unsigned int BurgerTimeController::get_initial_map() {
    return initial_map;
}

void BurgerTimeController::set_initial_map(unsigned int new_initial_map) {
    initial_map = new_initial_map;
}

bool BurgerTimeController::is_window_on_focus() const {
    return is_in_focus;
}

void BurgerTimeController::set_letterbox_view(int windowWidth, int windowHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = letter_view.getSize().x / (float) letter_view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    letter_view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
}

const std::vector<sf::Vector2u>& BurgerTimeController::get_available_resolutions() const {
    return available_resolutions;
}
