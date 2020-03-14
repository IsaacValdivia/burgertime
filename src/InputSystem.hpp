#pragma once

#include <cstdint>

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
} // namespace InputSystem
