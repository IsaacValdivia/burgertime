#include "InputSystem.hpp"

#include <map>
#include <set>
#include <SFML/Window.hpp>

namespace InputSystem
{
    namespace
    {
        static std::map<Input, sf::Keyboard::Key> inputMappings = {
            {Input::UP, sf::Keyboard::Key::W},
            {Input::DOWN, sf::Keyboard::Key::S},
            {Input::LEFT, sf::Keyboard::Key::A},
            {Input::RIGHT, sf::Keyboard::Key::D},
            {Input::PEPPER, sf::Keyboard::Key::Space},
            {Input::PAUSE, sf::Keyboard::Key::Escape},
        };

        static std::set<Input> currentPressedInputs;
        static std::set<Input> justPressedInputs;
        static std::set<Input> justReleasedInputs;
    }

    bool isInputPressed(Input input, const std::set<Input> &pressedInputs)
    {
        return pressedInputs.find(input) != pressedInputs.end();
    }

    void update()
    {
        std::set<Input> pressedInputs;
        justPressedInputs.clear();
        justReleasedInputs.clear();

        for (const auto &mapping : inputMappings)
        {
            Input input = mapping.first;
            sf::Keyboard::Key key = mapping.second;

            if (sf::Keyboard::isKeyPressed(key))
            {
                pressedInputs.insert(input);
            }
            else 
            {
                pressedInputs.erase(input);
            }

            if (!isInputPressed(input, currentPressedInputs) && isInputPressed(input, pressedInputs))
            {
                justPressedInputs.insert(input);
            }
            else if (isInputPressed(input, currentPressedInputs) && !isInputPressed(input, pressedInputs))
            {
                justReleasedInputs.insert(input);
            }
        }

        currentPressedInputs = pressedInputs;
    }

    bool isSingleInputActive(Input input)
    {
        return isInputPressed(input, currentPressedInputs);
    }

    bool hasInputJustBeenPressed(Input input)
    {
        return isInputPressed(input, justPressedInputs);
    }

    bool hasInputJustBeenReleased(Input input)
    {
        return isInputPressed(input, justReleasedInputs);
    }
} // namespace InputSystem
