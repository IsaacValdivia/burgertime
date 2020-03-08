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
        NUM_INPUTS
    };

    void update();

    bool isSingleInputActive(Input input);

    bool hasInputJustBeenPressed(Input input);

    bool hasInputJustBeenReleased(Input input);
} // namespace InputSystem
