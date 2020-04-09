#pragma once

#include <cstdint>
#include <map>
#include <fstream>
#include <SFML/Window.hpp>

namespace InputSystem {
    enum class Input {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ACTION,
        EXIT,
        DELETE,
        NUM_INPUTS
    };

    // TODO
    void updateLastKey(sf::Keyboard::Key newKey);

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


