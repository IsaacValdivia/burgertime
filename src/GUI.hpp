#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class GUI
{
public:
    static GUI &get();

    ~GUI();

    std::weak_ptr<sf::Text> createText(const std::string &id, const std::string &text, 
        sf::Vector2u screenPos = sf::Vector2u(0, 0), sf::Vector2f scale = sf::Vector2f(1, 1), sf::Color color = sf::Color::White);

    std::weak_ptr<sf::Text> getText(const std::string &id);

    static constexpr auto HORIZONTAL_DIVISIONS = WINDOW_WIDTH / 1000.0;
    static constexpr auto VERTICAL_DIVISIONS = WINDOW_HEIGHT / 1000.0;

private:
    GUI();

    GUI(const GUI &copy);

    GUI &operator=(const GUI &copy);


    std::shared_ptr<sf::Sprite> createSprite();

    std::map<std::string, std::shared_ptr<sf::Text>> guiTexts;
    sf::Font font;
};
