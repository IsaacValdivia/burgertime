#pragma once

#include <cstdint>
#include <map>
#include <fstream>
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
        ACTION,
        EXIT,
        DELETE,
        NUM_INPUTS
    };

    void updateLastKey(sf::Keyboard::Key newKey);
    void update();
    void update(char newChar);

    Input getLastInput();

    sf::Keyboard::Key getLastKey();

    void resetLastKey();

    bool isKeyBinded(sf::Keyboard::Key key);

    bool isSingleInputActive(Input input);

    bool hasInputJustBeenPressed(Input input);

    bool hasInputJustBeenReleased(Input input);

    bool hasEnteredText();

    char getCurrentChar();

    void setInputBinding(Input inp, sf::Keyboard::Key newKey);

    sf::Keyboard::Key inputToKey(Input inp);

    std::string keyboardKeyToString(sf::Keyboard::Key key);

    void writeBindings(std::ofstream &file);

    void readBindings(std::ifstream &file);

} // namespace InputSystem
