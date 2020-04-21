#pragma once

#include <cstdint>
#include <fstream>
#include <map>
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

    /**
     * @brief Updates last key pressed to newKey
     *
     * @param newKey latest key pressed
     */
    void update_last_key(sf::Keyboard::Key newKey);

    /**
     * @brief Main control function
     *
     */
    void update();

    /**
     * @brief Main control functions
     *
     * @param newChar
     */
    void update(char newChar);

    /**
     * @brief Get the last input
     *
     * @return Input
     */
    Input get_last_input();

    /**
     * @brief Get the last key
     *
     * @return sf::Keyboard::Key
     */
    sf::Keyboard::Key get_last_key();

    /**
     * @brief Resets last key pressed
     *
     */
    void reset_last_key();

    /**
     * @brief Returns if a key is binded
     *
     * @param key
     * @return true
     * @return false
     */
    bool is_key_binded(sf::Keyboard::Key key);

    /**
     * @brief Checks if single input is active
     *
     * @param input
     * @return true
     * @return false
     */
    bool is_single_input_active(Input input);

    /**
     * @brief Checks if input has just been pressed
     *
     * @param input
     * @return true
     * @return false
     */
    bool has_input_just_been_pressed(Input input);

    /**
     * @brief Checks if input has been released
     *
     * @param input
     * @return true
     * @return false
     */
    bool has_input_just_been_released(Input input);

    /**
     * @brief Checks if text has been entered
     *
     * @return true
     * @return false
     */
    bool has_entered_text();

    /**
     * @brief Get the current char
     *
     * @return char
     */
    char get_current_char();

    /**
     * @brief Set input binding
     *
     * @param inp
     * @param newKey
     */
    void set_input_binding(Input inp, sf::Keyboard::Key newKey);

    /**
     * @brief Set input binding
     *
     * @param inp
     * @return sf::Keyboard::Key
     */
    sf::Keyboard::Key set_input_binding(Input inp);

    /**
     * @brief Converts key to string
     *
     * @param key
     * @return std::string
     */
    std::string keyboard_key_to_string(sf::Keyboard::Key key);

    /**
     * @brief Writes bindings to a file
     *
     * @param file
     */
    void write_bindings(std::ofstream &file);

    /**
     * @brief Reads bindings from a file
     *
     * @param file
     */
    void read_bindings(std::ifstream &file);

    /**
     * @brief Converts an input to a key
     *
     * @param inp
     * @return sf::Keyboard::Key
     */
    sf::Keyboard::Key input_to_key(Input inp);
}