#include "InputSystem.hpp"

#include <list>
#include <set>

namespace InputSystem {
    namespace {
        static std::map<Input, sf::Keyboard::Key> input_mappings = {
            {Input::UP, sf::Keyboard::Key::W},
            {Input::DOWN, sf::Keyboard::Key::S},
            {Input::LEFT, sf::Keyboard::Key::A},
            {Input::RIGHT, sf::Keyboard::Key::D},
            {Input::ACTION, sf::Keyboard::Key::Space},
            {Input::EXIT, sf::Keyboard::Key::Escape},
            {Input::DELETE, sf::Keyboard::Key::BackSpace},
        };

        static std::map<sf::Keyboard::Key, std::string> KEY_TO_STRING = {
            {sf::Keyboard::Key::A, "A"},
            {sf::Keyboard::Key::B, "B"},
            {sf::Keyboard::Key::C, "C"},
            {sf::Keyboard::Key::D, "D"},
            {sf::Keyboard::Key::E, "E"},
            {sf::Keyboard::Key::F, "F"},
            {sf::Keyboard::Key::G, "G"},
            {sf::Keyboard::Key::H, "H"},
            {sf::Keyboard::Key::I, "I"},
            {sf::Keyboard::Key::J, "J"},
            {sf::Keyboard::Key::K, "K"},
            {sf::Keyboard::Key::L, "L"},
            {sf::Keyboard::Key::M, "M"},
            {sf::Keyboard::Key::N, "N"},
            {sf::Keyboard::Key::O, "O"},
            {sf::Keyboard::Key::P, "P"},
            {sf::Keyboard::Key::Q, "Q"},
            {sf::Keyboard::Key::R, "R"},
            {sf::Keyboard::Key::S, "S"},
            {sf::Keyboard::Key::T, "T"},
            {sf::Keyboard::Key::U, "U"},
            {sf::Keyboard::Key::V, "V"},
            {sf::Keyboard::Key::W, "W"},
            {sf::Keyboard::Key::X, "X"},
            {sf::Keyboard::Key::Y, "Y"},
            {sf::Keyboard::Key::Z, "Z"},
            {sf::Keyboard::Key::Num0, "0"},
            {sf::Keyboard::Key::Num1, "1"},
            {sf::Keyboard::Key::Num2, "2"},
            {sf::Keyboard::Key::Num3, "3"},
            {sf::Keyboard::Key::Num4, "4"},
            {sf::Keyboard::Key::Num5, "5"},
            {sf::Keyboard::Key::Num6, "6"},
            {sf::Keyboard::Key::Num7, "7"},
            {sf::Keyboard::Key::Num8, "8"},
            {sf::Keyboard::Key::Num9, "9"},
            {sf::Keyboard::Key::Escape, "ESC"},
            {sf::Keyboard::Key::LControl, "LCTRL"},
            {sf::Keyboard::Key::LShift, "LSHIFT"},
            {sf::Keyboard::Key::LAlt, "LALT"},
            {sf::Keyboard::Key::LSystem, "LSYST"},
            {sf::Keyboard::Key::RControl, "RCTRL"},
            {sf::Keyboard::Key::RShift, "RSHIFT"},
            {sf::Keyboard::Key::RAlt, "RALT"},
            {sf::Keyboard::Key::RSystem, "RSYST"},
            {sf::Keyboard::Key::Menu, "MENU"},
            {sf::Keyboard::Key::LBracket, "{"},
            {sf::Keyboard::Key::RBracket, "}"},
            {sf::Keyboard::Key::SemiColon, ";"},
            {sf::Keyboard::Key::Comma, ","},
            {sf::Keyboard::Key::Period, "."},
            {sf::Keyboard::Key::Quote, "\""},
            {sf::Keyboard::Key::Slash, "/"},
            {sf::Keyboard::Key::BackSlash, "\\"},
            {sf::Keyboard::Key::Tilde, "\'"},
            {sf::Keyboard::Key::Equal, "="},
            {sf::Keyboard::Key::Dash, "-"},
            {sf::Keyboard::Key::Space, "SPACE"},
            {sf::Keyboard::Key::Return, "RETURN"},
            {sf::Keyboard::Key::BackSpace, "BACK"},
            {sf::Keyboard::Key::Tab, "TAB"},
            {sf::Keyboard::Key::PageUp, "PGUP"},
            {sf::Keyboard::Key::PageDown, "PGDN"},
            {sf::Keyboard::Key::End, "END"},
            {sf::Keyboard::Key::Home, "HOME"},
            {sf::Keyboard::Key::Insert, "INS"},
            {sf::Keyboard::Key::Delete, "DEL"},
            {sf::Keyboard::Key::Add, "+"},
            {sf::Keyboard::Key::Subtract, "-"},
            {sf::Keyboard::Key::Multiply, "*"},
            {sf::Keyboard::Key::Divide, "/"},
            {sf::Keyboard::Key::Left, "LEFT"},
            {sf::Keyboard::Key::Right, "RIGHT"},
            {sf::Keyboard::Key::Up, "UP"},
            {sf::Keyboard::Key::Down, "DOWN"},
            {sf::Keyboard::Key::Numpad0, "NPAD0"},
            {sf::Keyboard::Key::Numpad1, "NPAD1"},
            {sf::Keyboard::Key::Numpad2, "NPAD2"},
            {sf::Keyboard::Key::Numpad3, "NPAD3"},
            {sf::Keyboard::Key::Numpad4, "NPAD4"},
            {sf::Keyboard::Key::Numpad5, "NPAD5"},
            {sf::Keyboard::Key::Numpad6, "NPAD6"},
            {sf::Keyboard::Key::Numpad7, "NPAD7"},
            {sf::Keyboard::Key::Numpad8, "NPAD8"},
            {sf::Keyboard::Key::Numpad9, "NPAD9"},
            {sf::Keyboard::Key::F1, "F1"},
            {sf::Keyboard::Key::F2, "F2"},
            {sf::Keyboard::Key::F3, "F3"},
            {sf::Keyboard::Key::F4, "F4"},
            {sf::Keyboard::Key::F5, "F5"},
            {sf::Keyboard::Key::F6, "F6"},
            {sf::Keyboard::Key::F7, "F7"},
            {sf::Keyboard::Key::F8, "F8"},
            {sf::Keyboard::Key::F9, "F9"},
            {sf::Keyboard::Key::F10, "F10"},
            {sf::Keyboard::Key::F11, "F11"},
            {sf::Keyboard::Key::F12, "F12"},
            {sf::Keyboard::Key::F13, "F13"},
            {sf::Keyboard::Key::F14, "F14"},
            {sf::Keyboard::Key::F15, "F15"},
            {sf::Keyboard::Key::Pause, "PAUSE"},
        };

        static std::list<Input> orderedPressedInputs;
        static std::set<Input> currentPressedInputs;
        static std::set<Input> justPressedInputs;
        static std::set<Input> justReleasedInputs;
        static sf::Keyboard::Key lastKey;
        static bool isCharEntered = false;
        static char charEntered;
    }

    std::string keyboardKeyToString(sf::Keyboard::Key key)
    {
        return KEY_TO_STRING[key];
    }

    sf::Keyboard::Key inputToKey(Input inp)
    {
        return inputBindings[inp];
    }

    void setInputBinding(Input inp, sf::Keyboard::Key newKey)
    {
        inputBindings[inp] = newKey;
    }

    void writeBindings(std::ofstream &file)
    {
        for (const auto &binding : inputBindings)
        {
            file.write(reinterpret_cast<const char*>(&binding.first), sizeof(binding.first));
            file.write(reinterpret_cast<const char*>(&binding.second), sizeof(binding.second));
        }
    }

    void readBindings(std::ifstream &file)
    {
        for (int i = 0; i < inputBindings.size(); ++i)
        {
            Input input;
            sf::Keyboard::Key key;

            file.read(reinterpret_cast<char*>(&input), sizeof(input));
            file.read(reinterpret_cast<char*>(&key), sizeof(key));

            inputBindings[input] = key;
        }
    }

    bool isInputPressed(Input input, const std::set<Input> &pressedInputs)
    {
        return pressedInputs.find(input) != pressedInputs.end();
    }

    bool isKeyBinded(sf::Keyboard::Key key)
    {
        for (const auto &inp : inputBindings)
        {
            if (inp.second == key)
            {
                return true;
            }
        }

        return false;
    }

    void updateLastKey(sf::Keyboard::Key newKey)
    {
        lastKey = newKey;
    }

    void resetLastKey()
    {
        lastKey = sf::Keyboard::Key::Unknown;
    }

    void updateCommon()
    {
        std::set<Input> pressedInputs;
        justPressedInputs.clear();
        justReleasedInputs.clear();

        for (const auto &mapping : inputBindings)
        {
            Input input = mapping.first;
            sf::Keyboard::Key key = mapping.second;

            if (sf::Keyboard::isKeyPressed(key)) {
                pressed_inputs.insert(input);
            }
            else
            {
                pressedInputs.erase(input);
            }

            if (!is_input_pressed(input, current_pressed_inputs) &&
                    is_input_pressed(input, pressed_inputs)) {

                ordered_pressed_inputs.push_back(input);
                just_pressed_inputs.insert(input);
            }
            else if (is_input_pressed(input, current_pressed_inputs) &&
                     !is_input_pressed(input, pressed_inputs)) {

                ordered_pressed_inputs.remove(input);
                just_released_inputs.insert(input);
            }
        }

        current_pressed_inputs = pressed_inputs;
    }

    void update() {
        is_char_entered = false;
        update_common();
    }

    void update(const char new_char) {
        is_char_entered = true;
        char_entered = new_char;
        update_common();
    }

    Input get_last_input() {
        if (ordered_pressed_inputs.size() > 0) {
            return ordered_pressed_inputs.back();
        }
        else {
            return Input::NONE;
        }

    }

    sf::Keyboard::Key getLastKey()
    {
        return lastKey;
    }

    bool is_single_input_active(const Input input) {
        return is_input_pressed(input, current_pressed_inputs);
    }

    bool has_input_just_been_pressed(const Input input) {
        return is_input_pressed(input, just_pressed_inputs);
    }

    bool has_input_just_been_released(const Input input) {
        return is_input_pressed(input, just_released_inputs);
    }

    bool has_entered_text() {
        return is_char_entered;
    }

    char get_current_char() {
        if (is_char_entered) {
            return char_entered;
        }
        else {
            return '\0';
        }
    }
}
