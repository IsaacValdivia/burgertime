#include "MainScreenStateMachine.hpp"

#include "InputSystem.hpp"

#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

FSM_INITIAL_STATE(MainScreenStateMachine, EnterStateMainScreen)

BurgerTimeController &MainScreenStateMachine::controller = BurgerTimeController::get();
GUI &MainScreenStateMachine::gui = GUI::get();

void EnterStateMainScreen::entry() {
    controller.clear_screen();

    if (!Audio::is_playing(Audio::MusicTrack::MENU_MUSIC)) {
        Audio::play(Audio::MusicTrack::MENU_MUSIC);
    }

    auto burger_time_text = gui.get_text("burTime").lock();

    auto start_text = gui.create_text("enterStateMainStart", "START",
                                      sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));
    auto instructions_text = gui.create_text("enterStateMainInstructions", "INSTRUCTIONS",
                                        sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));
    auto options_text = gui.create_text("enterStateMainOptions", "SETTINGS",
                                        sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));
    auto exit_text = gui.create_text("enterStateMainExit", "EXIT",
                                     sf::Vector2u(320, 600), sf::Vector2f(0.8, 0.8));


    auto enter_help = gui.create_text("mainScreenEnterHelp",
                                      "PRESS <" + std::string(InputSystem::keyboard_key_to_string(InputSystem::input_to_key(InputSystem::Input::ENTER_MENU)) + "> TO INTERACT"),
                                      sf::Vector2u(40, 960),
                                      sf::Vector2f(0.28, 0.28));

    auto go_back_help = gui.create_text("mainScreenGoBackHelp",
                                        "PRESS <" + std::string(InputSystem::keyboard_key_to_string(InputSystem::input_to_key(InputSystem::Input::BACK_MENU)) + "> TO GO BACK"),
                                        sf::Vector2u(620, 960),
                                        sf::Vector2f(0.28, 0.28));

    controller.add_drawable(burger_time_text);
    controller.add_drawable(gui.get_text("mainScreenEnterHelp"));
    controller.add_drawable(enter_help);
    controller.add_drawable(instructions_text);
    controller.add_drawable(start_text);
    controller.add_drawable(options_text);
    controller.add_drawable(exit_text);
}

void EnterStateMainScreen::react(const ExecuteEvent &) {
    transit<StartOptionState>();
}

void StartOptionState::entry() {
    gui.get_text("enterStateMainStart").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("enterStateMainInstructions").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainOptions").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainExit").lock()->setFillColor(sf::Color::White);
}

void StartOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<LevelScreenEnterState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<ExitOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<InstructionsOptionState>();
    }
}


void InstructionsOptionState::entry() {
    gui.get_text("enterStateMainStart").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainInstructions").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("enterStateMainOptions").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainExit").lock()->setFillColor(sf::Color::White);
}

void InstructionsOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<FinishedGoToInstructionsState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<StartOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<ConfigOptionState>();
    }
}


void ConfigOptionState::entry() {
    gui.get_text("enterStateMainStart").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainInstructions").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainOptions").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("enterStateMainExit").lock()->setFillColor(sf::Color::White);
}

void ConfigOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<InsideConfigOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<InstructionsOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<ExitOptionState>();
    }
}

void InsideConfigOptionState::entry() {
    controller.clear_screen();

    auto bindings_text = gui.create_text("insideConfigMainBindings", "CONTROLS",
                                         sf::Vector2u(320, 300), sf::Vector2f(0.8, 0.8));

    auto music_text = gui.create_text("insideConfigMainSoundMusic", "SOUND & MUSIC",
                                         sf::Vector2u(320, 400), sf::Vector2f(0.8, 0.8));

    auto resolution_text = gui.create_text("insideConfigMainResolution", "RESOLUTION",
                                           sf::Vector2u(320, 500), sf::Vector2f(0.8, 0.8));

    auto back_text = gui.create_text("insideConfigMainBack", "BACK", sf::Vector2u(320, 600),
                                     sf::Vector2f(0.8, 0.8));

    controller.add_drawable(gui.get_text("burTime"));
    controller.add_drawable(gui.get_text("mainScreenEnterHelp"));
    controller.add_drawable(gui.get_text("mainScreenGoBackHelp"));
    controller.add_drawable(bindings_text);
    controller.add_drawable(music_text);
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

    auto help = gui.create_text("bindingsScreenHelp", "PRESS ENTER TO CHANGE", sf::Vector2u(42, 220),
                              sf::Vector2f(0.8, 0.8), sf::Color::White);

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

    auto action = gui.create_text("bindingsScreenAction", "PEPPER",
                                  sf::Vector2u(320, 700), sf::Vector2f(0.8, 0.8));
    auto action_key = gui.create_text("bindingsScreenActionKey",
                                      InputSystem::keyboard_key_to_string(
                                          InputSystem::input_to_key(
                                                  InputSystem::Input::PEPPER)),
                                      sf::Vector2u(700, 700), sf::Vector2f(0.8, 0.8));

    auto exit = gui.create_text("bindingsScreenExit", "PAUSE",
                                sf::Vector2u(320, 800), sf::Vector2f(0.8, 0.8));

    auto exit_key = gui.create_text("bindingsScreenExitKey",
                                    InputSystem::keyboard_key_to_string(
                                        InputSystem::input_to_key(InputSystem::Input::PAUSE)),
                                    sf::Vector2u(700, 800), sf::Vector2f(0.8, 0.8));

    auto back = gui.create_text("bindingsScreenBack", "BACK",
                                sf::Vector2u(320, 900), sf::Vector2f(0.8, 0.8));

    auto back_help = gui.create_text("bindingsScreenBackHelp", "PRESS <" + std::string(InputSystem::keyboard_key_to_string(InputSystem::input_to_key(InputSystem::Input::BACK_MENU)) + "> TO GO BACK"),
                                     sf::Vector2u(620, 960),
                                     sf::Vector2f(0.28, 0.28));

    controller.add_drawable(gui.get_text("burTime"));
    controller.add_drawable(gui.get_text("mainScreenEnterHelp"));
    controller.add_drawable(back_help);
    controller.add_drawable(help);
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
    if (is_reading_key && has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        is_reading_key = false;
        update_color = true;
        new_color = sf::Color::Cyan;
    }
    else if (has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<InsideConfigOptionState>();
        return;
    }
    else if (is_reading_key) {
        auto help_text = gui.get_text("bindingsScreenHelp").lock();
        help_text->setString("PRESS KEY TO OVERRIDE");

        auto back_help_text = gui.get_text("bindingsScreenBackHelp").lock();
        back_help_text->setString("PRESS <" + std::string(InputSystem::keyboard_key_to_string(InputSystem::input_to_key(InputSystem::Input::BACK_MENU))) + "> TO CANCEL");

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
                    InputSystem::set_input_binding(InputSystem::Input::PEPPER, new_key);
                    option_text = "bindingsScreenActionKey";
                    break;
                case EXIT:
                    InputSystem::set_input_binding(InputSystem::Input::PAUSE, new_key);
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
    else {
        auto help_text = gui.get_text("bindingsScreenHelp").lock();
        help_text->setString("PRESS ENTER TO CHANGE");

        auto back_help_text = gui.get_text("bindingsScreenBackHelp").lock();
        back_help_text->setString("PRESS <" + std::string(InputSystem::keyboard_key_to_string(InputSystem::input_to_key(InputSystem::Input::BACK_MENU)) + "> TO GO BACK"));

        if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
            Audio::play(Audio::Track::MENU_SELECT);
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
        else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
            Audio::play(Audio::Track::MENU_MOVE);
            is_reading_key = false;
            update_color = true;
            new_color = sf::Color::Cyan;
            current_option = static_cast<CurrentOption>(((current_option - 1)
                            + NUM_OPTIONS) % NUM_OPTIONS);
        }
        else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
            Audio::play(Audio::Track::MENU_MOVE);
            is_reading_key = false;
            update_color = true;
            new_color = sf::Color::Cyan;
            current_option = static_cast<CurrentOption>((current_option + 1) %
                            NUM_OPTIONS);
        }
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
    gui.get_text("insideConfigMainSoundMusic").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainResolution").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainBack").lock()->setFillColor(sf::Color::White);
}

void BindingsOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<BindingsScreenInsideState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<BackOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<SoundMusicOptionState>();
    }
}


void SoundMusicOptionState::entry() {
    gui.get_text("insideConfigMainBindings").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainSoundMusic").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("insideConfigMainResolution").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainBack").lock()->setFillColor(sf::Color::White);
}

void SoundMusicOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<SoundMusicScreenInsideState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<BindingsOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<ResolutionOptionState>();
    }
}

void SoundMusicScreenInsideState::update_texts() const {
    auto effects_text = gui.get_text("soundMusicScreenEffects").lock();
    auto effects_value = gui.get_text("soundMusicScreenEffectsVal").lock();

    if (sfx_vol == MIN_VOLUME) {
        effects_value->setString("  " + std::to_string(sfx_vol) + " >");
    } 
    else if (sfx_vol == MAX_VOLUME) {
        effects_value->setString("< " + std::to_string(sfx_vol) + "  ");
    }
    else {
        effects_value->setString("< " + std::to_string(sfx_vol) + " >");
    }

    auto sound_text = gui.get_text("soundMusicScreenSound").lock();
    auto sound_value = gui.get_text("soundMusicScreenSoundVal").lock();
    sound_value->setString("< " + std::to_string(music_vol) + " >");

    if (music_vol == MIN_VOLUME) {
        sound_value->setString("  " + std::to_string(music_vol) + " >");
    } 
    else if (music_vol == MAX_VOLUME) {
        sound_value->setString("< " + std::to_string(music_vol) + "  ");
    }
    else {
        sound_value->setString("< " + std::to_string(music_vol) + " >");
    }

    auto exit_text = gui.get_text("soundMusicScreenExit").lock();

    switch (current_state) {
        case SFX:
            effects_text->setFillColor(sf::Color::Cyan);
            effects_value->setFillColor(sf::Color::Cyan);
            sound_text->setFillColor(sf::Color::White);
            sound_value->setFillColor(sf::Color::White);
            exit_text->setFillColor(sf::Color::White);
            break;
        case MUSIC:
            effects_text->setFillColor(sf::Color::White);
            effects_value->setFillColor(sf::Color::White);
            sound_text->setFillColor(sf::Color::Cyan);
            sound_value->setFillColor(sf::Color::Cyan);
            exit_text->setFillColor(sf::Color::White);
            break;
        case BACK:
            effects_text->setFillColor(sf::Color::White);
            effects_value->setFillColor(sf::Color::White);
            sound_text->setFillColor(sf::Color::White);
            sound_value->setFillColor(sf::Color::White);
            exit_text->setFillColor(sf::Color::Cyan);
            break;
        default:
            throw std::runtime_error("Unknown state for SOUND & MUSIC screen");
    }
}

void SoundMusicScreenInsideState::entry() {
    controller.clear_screen();

    auto &config = Config::get();

    sfx_vol = config.get_sfx_volume();
    music_vol = config.get_music_volume();
    current_state = SFX;

    auto effects_text = gui.create_text("soundMusicScreenEffects", "SFX VOLUME",
                                        sf::Vector2u(100, 300), sf::Vector2f(0.8, 0.8), sf::Color::Cyan);

    auto effects_value = gui.create_text("soundMusicScreenEffectsVal", "  " + std::to_string(sfx_vol) + "  ",
                                         sf::Vector2u(660, 300), sf::Vector2f(0.8, 0.8), sf::Color::Cyan);

    auto sound_text = gui.create_text("soundMusicScreenSound", "MUSIC VOLUME",
                                      sf::Vector2u(100, 400), sf::Vector2f(0.8, 0.8));

    auto sound_value = gui.create_text("soundMusicScreenSoundVal", "  " + std::to_string(music_vol) + "  ",
                                       sf::Vector2u(660, 400), sf::Vector2f(0.8, 0.8));

    auto exit_text = gui.create_text("soundMusicScreenExit", "BACK", sf::Vector2u(100, 500), sf::Vector2f(0.8, 0.8));


    controller.add_drawable(gui.get_text("burTime"));
    controller.add_drawable(gui.get_text("mainScreenGoBackHelp"));
    controller.add_drawable(effects_text);
    controller.add_drawable(effects_value);
    controller.add_drawable(sound_text);
    controller.add_drawable(sound_value);
    controller.add_drawable(exit_text);
}

void SoundMusicScreenInsideState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<InsideConfigOptionState>();
        return;
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        switch (current_state) {
            case SFX:
                current_state = BACK;
                break;
            case MUSIC:
                current_state = SFX;
                break;
            case BACK:
                current_state = MUSIC;
                break;
            default:
                throw std::runtime_error("Unknown state for SOUND & MUSIC screen");
        }
        Audio::play(Audio::Track::MENU_MOVE);
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        switch (current_state) {
            case SFX:
                current_state = MUSIC;
                break;
            case MUSIC:
                current_state = BACK;
                break;
            case BACK:
                current_state = SFX;
                break;
            default:
                throw std::runtime_error("Unknown state for SOUND & MUSIC screen");
        }
        Audio::play(Audio::Track::MENU_MOVE);
    }
    else if (has_input_just_been_pressed(InputSystem::Input::LEFT_MENU)) {
        switch (current_state) {
            case SFX:
                if (sfx_vol != MIN_VOLUME) {
                    sfx_vol = sfx_vol - VOLUME_GRANULARITY;
                    Audio::set_sfx_vol(sfx_vol);
                    Config::get().set_sfx_vol(sfx_vol);
                    Config::get().write_file();
                    Audio::play(Audio::Track::MENU_MOVE);
                }
                break;
            case MUSIC:
                if (music_vol != MIN_VOLUME) {
                    music_vol = music_vol - VOLUME_GRANULARITY;
                    Audio::set_music_vol(music_vol);
                    Config::get().set_music_vol(music_vol);
                    Config::get().write_file();
                    Audio::play(Audio::Track::MENU_MOVE);
                }
                break;
            case BACK:
                // Nothing to do
                break;
            default:
                throw std::runtime_error("Unknown state for SOUND & MUSIC screen");
        }
    }
    else if (has_input_just_been_pressed(InputSystem::Input::RIGHT_MENU)) {
        switch (current_state) {
            case SFX:
                if (sfx_vol != MAX_VOLUME) {
                    sfx_vol = sfx_vol + VOLUME_GRANULARITY;
                    Audio::set_sfx_vol(sfx_vol);
                    Config::get().set_sfx_vol(sfx_vol);
                    Config::get().write_file();
                    Audio::play(Audio::Track::MENU_MOVE);
                }
                break;
            case MUSIC:
                if (music_vol != MAX_VOLUME) {
                    music_vol = music_vol + VOLUME_GRANULARITY;
                    Audio::set_music_vol(music_vol);
                    Config::get().set_music_vol(music_vol);
                    Config::get().write_file();
                    Audio::play(Audio::Track::MENU_MOVE);
                }
                break;
            case BACK:
                // Nothing to do
                break;
            default:
                throw std::runtime_error("Unknown state for SOUND & MUSIC screen");
        }
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        switch (current_state) {
            case SFX:
            case MUSIC:
                // Nothing to do
                break;
            case BACK:
                Audio::play(Audio::Track::MENU_SELECT);
                transit<InsideConfigOptionState>();
                return;
            default:
                throw std::runtime_error("Unknown state for SOUND & MUSIC screen");
        }
    }

    update_texts();
}


void ResolutionScreenInsideState::change_resolutions_text() const {
    auto resolution_text = gui.get_text("resolutionScreenResText").lock();
    auto resolution_value = gui.get_text("resolutionScreenResVal").lock();
    resolution_value->setString("< " + std::to_string(current_resolution_it->x) + "x" + std::to_string(current_resolution_it->y) + " >");

    if (current_resolution_it == BurgerTimeController::get().get_available_resolutions().begin()) {
        resolution_value->setString("  " + std::to_string(current_resolution_it->x) + "x" + std::to_string(current_resolution_it->y) + " >");
    } 
    else if (current_resolution_it == BurgerTimeController::get().get_available_resolutions().end() - 1) {
        resolution_value->setString("< " + std::to_string(current_resolution_it->x) + "x" + std::to_string(current_resolution_it->y) + "  ");
    }
    else {
        resolution_value->setString("< " + std::to_string(current_resolution_it->x) + "x" + std::to_string(current_resolution_it->y) + " >");
    }

    auto borders_text = gui.get_text("resolutionScreenBordersText").lock();
    auto borders_value = gui.get_text("resolutionScreenBordersVal").lock();
    auto borders_value_text = are_borders_on ? "ON" : "OFF";
    borders_value->setString("< " + std::string(borders_value_text) + " >");

    auto exit_text = gui.get_text("soundMusicScreenExit").lock();

    switch (current_state) {
        case CHANGE_RESOLUTION:
            resolution_text->setFillColor(sf::Color::Cyan);
            resolution_value->setFillColor(sf::Color::Cyan);
            borders_text->setFillColor(sf::Color::White);
            borders_value->setFillColor(sf::Color::White);
            exit_text->setFillColor(sf::Color::White);
            break;
        case BORDER_OR_NOT:
            resolution_text->setFillColor(sf::Color::White);
            resolution_value->setFillColor(sf::Color::White);
            borders_text->setFillColor(sf::Color::Cyan);
            borders_value->setFillColor(sf::Color::Cyan);
            exit_text->setFillColor(sf::Color::White);
            break;
        case BACK:
            resolution_text->setFillColor(sf::Color::White);
            resolution_value->setFillColor(sf::Color::White);
            borders_text->setFillColor(sf::Color::White);
            borders_value->setFillColor(sf::Color::White);
            exit_text->setFillColor(sf::Color::Cyan);
            break;
        default:
            throw std::runtime_error("Unknown state for RESOLUTION screen");
    }
}

void ResolutionScreenInsideState::entry() {
    controller.clear_screen();

    auto &config = Config::get();

    const auto &available_resolutions = BurgerTimeController::get().get_available_resolutions();
    current_resolution_it = std::find(available_resolutions.begin(), available_resolutions.end(), config.get_resolution());

    current_state = CHANGE_RESOLUTION;
    are_borders_on = config.get_are_borders_on();

    auto resolution_text = gui.create_text("resolutionScreenResText", "RESOLUTION",
                                        sf::Vector2u(100, 300), sf::Vector2f(0.8, 0.8), sf::Color::Cyan);
    auto resolution_value = gui.create_text("resolutionScreenResVal", "  " + std::to_string(current_resolution_it->x) + "x" + std::to_string(current_resolution_it->y) + "  ",
                                         sf::Vector2u(200, 400), sf::Vector2f(0.8, 0.8), sf::Color::Cyan);

    auto borders_text = gui.create_text("resolutionScreenBordersText", "BORDERS",
                                        sf::Vector2u(100, 500), sf::Vector2f(0.8, 0.8));
    auto borders_value_text = are_borders_on ? "ON" : "OFF";
    auto borders_value = gui.create_text("resolutionScreenBordersVal", "< " + std::string(borders_value_text) + " >",
                                         sf::Vector2u(200, 600), sf::Vector2f(0.8, 0.8));

    auto exit_text = gui.create_text("soundMusicScreenExit", "BACK", sf::Vector2u(100, 700), sf::Vector2f(0.8, 0.8));


    controller.add_drawable(gui.get_text("burTime"));
    controller.add_drawable(gui.get_text("mainScreenGoBackHelp"));
    controller.add_drawable(resolution_text);
    controller.add_drawable(resolution_value);
    controller.add_drawable(borders_text);
    controller.add_drawable(borders_value);
    controller.add_drawable(exit_text);
}

void ResolutionScreenInsideState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<InsideConfigOptionState>();
        return;
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        switch (current_state) {
            case CHANGE_RESOLUTION:
                current_state = BACK;
                break;
            case BORDER_OR_NOT:
                current_state = CHANGE_RESOLUTION;
                break;
            case BACK:
                current_state = BORDER_OR_NOT;
                break;
            default:
                throw std::runtime_error("Unknown state for RESOLUTION screen");
        }
        Audio::play(Audio::Track::MENU_MOVE);
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        switch (current_state) {
            case CHANGE_RESOLUTION:
                current_state = BORDER_OR_NOT;
                break;
            case BORDER_OR_NOT:
                current_state = BACK;
                break;
            case BACK:
                current_state = CHANGE_RESOLUTION;
                break;
            default:
                throw std::runtime_error("Unknown state for RESOLUTION screen");
        }
        Audio::play(Audio::Track::MENU_MOVE);
    }
    else if (has_input_just_been_pressed(InputSystem::Input::LEFT_MENU)) {
        switch (current_state) {
            case CHANGE_RESOLUTION:
                if (current_resolution_it != BurgerTimeController::get().get_available_resolutions().begin()) {
                    current_resolution_it--;
                    BurgerTimeController::get().set_resolution(*current_resolution_it);
                    Config::get().set_resolution(*current_resolution_it);
                    Config::get().write_file();
                    Audio::play(Audio::Track::MENU_MOVE);
                }
                break;
            case BORDER_OR_NOT:
                are_borders_on = !are_borders_on;
                Config::get().change_border_mode();
                Config::get().write_file();
                BurgerTimeController::get().window_borderless_switch();
                Audio::play(Audio::Track::MENU_MOVE);
                break;
            case BACK:
                // Nothing to do
                break;
            default:
                throw std::runtime_error("Unknown state for RESOLUTION screen");
        }
    }
    else if (has_input_just_been_pressed(InputSystem::Input::RIGHT_MENU)) {
        switch (current_state) {
            case CHANGE_RESOLUTION:
                if (current_resolution_it != BurgerTimeController::get().get_available_resolutions().end() - 1) {
                    current_resolution_it++;
                    BurgerTimeController::get().set_resolution(*current_resolution_it);
                    Config::get().set_resolution(*current_resolution_it);
                    Config::get().write_file();
                    Audio::play(Audio::Track::MENU_MOVE);
                }
                break;
            case BORDER_OR_NOT:
                are_borders_on = !are_borders_on;
                Config::get().change_border_mode();
                Config::get().write_file();
                BurgerTimeController::get().window_borderless_switch();
                Audio::play(Audio::Track::MENU_MOVE);
                break;
            case BACK:
                // Nothing to do
                break;
            default:
                throw std::runtime_error("Unknown state for RESOLUTION screen");
        }
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        switch (current_state) {
            case CHANGE_RESOLUTION:
                // Nothing to do
                break;
            case BORDER_OR_NOT:
                are_borders_on = !are_borders_on;
                Config::get().change_border_mode();
                Config::get().write_file();
                BurgerTimeController::get().window_borderless_switch();
                Audio::play(Audio::Track::MENU_MOVE);
                break;
            case BACK:
                Audio::play(Audio::Track::MENU_SELECT);
                transit<InsideConfigOptionState>();
                return;
            default:
                throw std::runtime_error("Unknown state for RESOLUTION screen");
        }
    }

    change_resolutions_text();
}


void ResolutionOptionState::entry() {
    gui.get_text("insideConfigMainBindings").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainSoundMusic").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainResolution").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("insideConfigMainBack").lock()->setFillColor(sf::Color::White);
}

void ResolutionOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<ResolutionScreenInsideState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<SoundMusicOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<BackOptionState>();
    }
}


void BackOptionState::entry() {
    gui.get_text("insideConfigMainBindings").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainSoundMusic").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainResolution").lock()->setFillColor(sf::Color::White);
    gui.get_text("insideConfigMainBack").lock()->setFillColor(sf::Color::Cyan);
}

void BackOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<ResolutionOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<BindingsOptionState>();
    }
}


void ExitOptionState::entry() {
    gui.get_text("enterStateMainStart").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainInstructions").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainOptions").lock()->setFillColor(sf::Color::White);
    gui.get_text("enterStateMainExit").lock()->setFillColor(sf::Color::Cyan);
}

void ExitOptionState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<FinishedExitState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<ConfigOptionState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<StartOptionState>();
    }
}


void LevelScreenEnterState::entry() {
    controller.clear_screen();

    auto maps_folder = fs::path(MAPS_FOLDER);
    num_maps = std::distance(fs::directory_iterator(maps_folder), fs::directory_iterator{}) / 2;

    if (num_maps == 0) {
        throw std::runtime_error(std::string("No maps found in ") + MAPS_FOLDER);
    }

    auto help_text1 = gui.create_text("levelStateHelp1", "PRESS ENTER TO START",
                                      sf::Vector2u(65, 300), sf::Vector2f(0.8, 0.8));

    auto help_text2 = gui.create_text("levelStateHelp2", "INITIAL MAP (1-" + std::to_string(num_maps) + ")",
                                     sf::Vector2u(120, 400), sf::Vector2f(0.8, 0.8));

    auto map_idx = gui.create_text("levelStateMapIdx", "_",
                                   sf::Vector2u(300, 500), sf::Vector2f(0.8, 0.8));

    controller.add_drawable(gui.get_text("burTime"));
    controller.add_drawable(gui.get_text("mainScreenEnterHelp"));
    controller.add_drawable(gui.get_text("mainScreenGoBackHelp"));
    controller.add_drawable(help_text1);
    controller.add_drawable(help_text2);
    controller.add_drawable(map_idx);
}

void LevelScreenEnterState::react(const ExecuteEvent &) {
    auto map_idx = gui.get_text("levelStateMapIdx").lock();
    auto map_idx_str = map_idx->getString();

    if (InputSystem::has_input_just_been_pressed(InputSystem::Input::DELETE)) {
        auto help_text1 = gui.get_text("levelStateHelp1").lock();
        help_text1->setString("PRESS ENTER TO START");

        if (map_idx_str.getSize() > 1) {
            map_idx_str = map_idx_str.substring(0, map_idx_str.getSize() - 1);
            map_idx_str[map_idx_str.getSize() - 1] = '_';
            map_idx->setString(map_idx_str);
        }
    }
    else if (InputSystem::has_entered_text() && map_idx_str.getSize() < 8) {
        auto help_text1 = gui.get_text("levelStateHelp1").lock();
        help_text1->setString("PRESS ENTER TO START");

        char new_char = InputSystem::get_current_char();
        if ('0' <= new_char && new_char <= '9') {
            map_idx_str[map_idx_str.getSize() - 1] = new_char;
            map_idx_str += '_';
            map_idx->setString(map_idx_str);
        }
    }
    else if (InputSystem::has_input_just_been_pressed(InputSystem::Input::ENTER_MENU) && map_idx_str.getSize() > 1) {
        auto map_idx = std::stoi(std::string(map_idx_str.substring(0, map_idx_str.getSize() - 1)));
        if (1 <= map_idx && map_idx <= num_maps) {
            controller.set_initial_map(map_idx - 1);
            Audio::play(Audio::Track::MENU_SELECT);
            transit<DifficultyScreenEnterState>();
        }
        else {
            auto help_text1 = gui.get_text("levelStateHelp1").lock();
            help_text1->setString(" INVALID MAP GIVEN");
        }
    }
    else if (InputSystem::has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<EnterStateMainScreen>();
    }
}


void DifficultyScreenEnterState::entry() {
    controller.clear_screen();

    auto classic_text = gui.create_text("difficultyStateClassic", "+ PTS - CLASSIC",
                                      sf::Vector2u(165, 300), sf::Vector2f(0.8, 0.8));
    auto hard_text = gui.create_text("difficultyStateHard", "++ PTS - HARD",
                                        sf::Vector2u(165, 400), sf::Vector2f(0.8, 0.8));
    auto smiley_text = gui.create_text("difficultyStateSmiley", "+++ PTS - :-)",
                                     sf::Vector2u(165, 500), sf::Vector2f(0.8, 0.8));

    auto help_text_1 = gui.create_text("difficultyStateHelp1", "",
                                     sf::Vector2u(140, 800), sf::Vector2f(0.28, 0.28));
    auto help_text_2 = gui.create_text("difficultyStateHelp2", "",
                                     sf::Vector2u(140, 820), sf::Vector2f(0.28, 0.28));

    controller.add_drawable(gui.get_text("burTime"));
    controller.add_drawable(gui.get_text("mainScreenEnterHelp"));
    controller.add_drawable(gui.get_text("mainScreenGoBackHelp"));
    controller.add_drawable(help_text_1);
    controller.add_drawable(help_text_2);
    controller.add_drawable(classic_text);
    controller.add_drawable(hard_text);
    controller.add_drawable(smiley_text);
}

void DifficultyScreenEnterState::react(const ExecuteEvent &) {
    transit<DifficultyScreenClassicState>();
}


void DifficultyScreenClassicState::entry() {
    gui.get_text("difficultyStateHelp1").lock()->setString("ENEMIES WILL CHASE YOU IN THE CLASSICAL MANNER");
    gui.get_text("difficultyStateHelp2").lock()->setString("");

    gui.get_text("difficultyStateClassic").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("difficultyStateHard").lock()->setFillColor(sf::Color::White);
    gui.get_text("difficultyStateSmiley").lock()->setFillColor(sf::Color::White);
}

void DifficultyScreenClassicState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        controller.set_difficulty(CLASSIC);
        transit<FinishedStartState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<DifficultyScreenSmileyState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<DifficultyScreenHardState>();
    }
}


void DifficultyScreenHardState::entry() {
    gui.get_text("difficultyStateHelp1").lock()->setString("ENEMIES WILL CHASE YOU, ASSUMING DIFFERENT");
    gui.get_text("difficultyStateHelp2").lock()->setString("ROLES AND PERFORMING SWARMING");

    gui.get_text("difficultyStateClassic").lock()->setFillColor(sf::Color::White);
    gui.get_text("difficultyStateHard").lock()->setFillColor(sf::Color::Cyan);
    gui.get_text("difficultyStateSmiley").lock()->setFillColor(sf::Color::White);
}

void DifficultyScreenHardState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        controller.set_difficulty(HARD);
        transit<FinishedStartState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<DifficultyScreenClassicState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<DifficultyScreenSmileyState>();
    }
}


void DifficultyScreenSmileyState::entry() {
    gui.get_text("difficultyStateHelp1").lock()->setString("ENEMIES WILL CHASE YOU AGGRESSIVELY, WHILE");
    gui.get_text("difficultyStateHelp2").lock()->setString("PERFORMING SWARMING");

    gui.get_text("difficultyStateClassic").lock()->setFillColor(sf::Color::White);
    gui.get_text("difficultyStateHard").lock()->setFillColor(sf::Color::White);
    gui.get_text("difficultyStateSmiley").lock()->setFillColor(sf::Color::Cyan);
}

void DifficultyScreenSmileyState::react(const ExecuteEvent &) {
    if (has_input_just_been_pressed(InputSystem::Input::BACK_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        transit<EnterStateMainScreen>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
        Audio::play(Audio::Track::MENU_SELECT);
        controller.set_difficulty(SMILEY);
        transit<FinishedStartState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::UP_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<DifficultyScreenHardState>();
    }
    else if (has_input_just_been_pressed(InputSystem::Input::DOWN_MENU)) {
        Audio::play(Audio::Track::MENU_MOVE);
        transit<DifficultyScreenClassicState>();
    }
}
