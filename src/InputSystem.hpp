#pragma once

#include <cstdint>
#include <map>
#include <SFML/Window.hpp>

namespace InputSystem
{
    enum class Input
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        PEPPER,
        PAUSE,
        DELETE,
        NUM_INPUTS
    };

    void update();
    void update(char newChar);

    Input getLastInput();

    bool isSingleInputActive(Input input);

    bool hasInputJustBeenPressed(Input input);

    bool hasInputJustBeenReleased(Input input);

    bool hasEnteredText();

    char getCurrentChar();

    void setInputBindings(const std::map<Input, sf::Keyboard::Key> &inputBindings);

    std::map<Input, sf::Keyboard::Key> getInputBindings();

} // namespace InputSystem
