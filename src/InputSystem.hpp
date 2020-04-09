#pragma once

#include <cstdint>

namespace InputSystem {
    enum class Input {
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

    /**
     * @brief Main control function
     *
     */
    void update();

    /**
     * @brief Main control function
     *
     * @param new_char new character
     */
    void update(const char new_char);

    /**
     * @brief Get the Last Input received
     *
     * @return Input object
     */
    Input get_last_input();

    /**
     * @brief Checks if the input has been pressed
     *
     * @param input key/input pressed
     * @return true
     * @return false
     */
    bool is_single_input_active(const Input input);

    /**
     * @brief Checks if the input has been pressed
     *
     * @param input key/input
     * @return true
     * @return false
     */
    bool has_input_just_been_pressed(const Input input);

    /**
     * @brief Checks if the input has been released
     *
     * @param input key/input
     * @return true
     * @return false
     */
    bool has_input_just_been_released(const Input input);

    /**
     * @brief Checks if a character has been entered
     *
     * @return true
     * @return false
     */
    bool has_entered_text();

    /**
     * @brief Get current character entered
     *
     * @return char character currently inserted
     */
    char get_current_char();
}
