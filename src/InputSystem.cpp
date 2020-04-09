#include "InputSystem.hpp"

#include <list>
#include <map>
#include <set>
#include <SFML/Window.hpp>

namespace InputSystem {
    namespace {
        static std::map<Input, sf::Keyboard::Key> input_mappings = {
            {Input::UP, sf::Keyboard::Key::W},
            {Input::DOWN, sf::Keyboard::Key::S},
            {Input::LEFT, sf::Keyboard::Key::A},
            {Input::RIGHT, sf::Keyboard::Key::D},
            {Input::PEPPER, sf::Keyboard::Key::Space},
            {Input::PAUSE, sf::Keyboard::Key::Escape},
            {Input::DELETE, sf::Keyboard::Key::BackSpace},
        };

        static std::list<Input> ordered_pressed_inputs;
        static std::set<Input> current_pressed_inputs;
        static std::set<Input> just_pressed_inputs;
        static std::set<Input> just_released_inputs;
        static bool is_char_entered = false;
        static char char_entered;
    }

    bool is_input_pressed(const Input input, const std::set<Input> &pressed_inputs) {
        return pressed_inputs.find(input) != pressed_inputs.end();
    }

    void update_common() {
        std::set<Input> pressed_inputs;
        just_pressed_inputs.clear();
        just_released_inputs.clear();

        for (const auto &mapping : input_mappings) {
            Input input = mapping.first;
            sf::Keyboard::Key key = mapping.second;

            if (sf::Keyboard::isKeyPressed(key)) {
                pressed_inputs.insert(input);
            }
            else {
                pressed_inputs.erase(input);
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
