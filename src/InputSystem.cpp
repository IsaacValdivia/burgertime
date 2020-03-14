#include "InputSystem.hpp"

#include <list>
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
            {Input::DELETE, sf::Keyboard::Key::BackSpace},
        };

        static std::list<Input> orderedPressedInputs;
        static std::set<Input> currentPressedInputs;
        static std::set<Input> justPressedInputs;
        static std::set<Input> justReleasedInputs;
        static bool isCharEntered = false;
        static char charEntered;
    }

    bool isInputPressed(Input input, const std::set<Input> &pressedInputs)
    {
        return pressedInputs.find(input) != pressedInputs.end();
    }

    void updateCommon()
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
                orderedPressedInputs.push_back(input);
                justPressedInputs.insert(input);
            }
            else if (isInputPressed(input, currentPressedInputs) && !isInputPressed(input, pressedInputs))
            {
                orderedPressedInputs.remove(input);
                justReleasedInputs.insert(input);
            }
        }

        currentPressedInputs = pressedInputs;
    }

    void update()
    {
        isCharEntered = false;
        updateCommon();
    }

    void update(char newChar)
    {
        isCharEntered = true;
        charEntered = newChar;
        updateCommon();
    }

    Input getLastInput()
    {
        if (orderedPressedInputs.size() > 0)
        {
            return orderedPressedInputs.back();
        }
        else
        {
            return Input::NONE;
        }
        
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

    bool hasEnteredText()
    {
        return isCharEntered;
    }

    char getCurrentChar()
    {
        if (isCharEntered)
        {
            return charEntered;
        }
        else
        {
            // TODO: change, do properly
            throw -1;
        }
    }
} // namespace InputSystem
