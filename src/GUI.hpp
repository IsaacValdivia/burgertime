#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class GUI {
private:
    /**
     * @brief Construct a new GUI object
     *
     */
    GUI();

    /**
     * @brief Construct a new GUI object, from an existing one
     *
     * @param copy
     */
    GUI(const GUI &copy);

    /**
     * @brief = Operator for GUI object
     *
     * @param copy
     * @return GUI&
     */
    GUI &operator=(const GUI &copy);

    /**
     * @brief Create a Sprite object
     *
     * @return std::shared_ptr<sf::Sprite>
     */
    std::shared_ptr<sf::Sprite> createSprite();

    std::map<std::string, std::shared_ptr<sf::Text>> gui_texts;
    sf::Font font;

public:

    static constexpr auto HORIZONTAL_DIVISIONS = WINDOW_WIDTH / 1000.0;
    static constexpr auto VERTICAL_DIVISIONS = WINDOW_HEIGHT / 1000.0;

    /**
     * Retrieves GUI singleton
     *
     * @return GUI&
     */
    static GUI &get();

    /**
     * @brief Destroy the GUI object
     *
     */
    ~GUI();

    /**
     * @brief Places a text in the specified position, with a certain color and scale
     *
     * @param id
     * @param text
     * @param screen_pos
     * @param scale
     * @param color
     * @return std::weak_ptr<sf::Text>
     */
    std::weak_ptr<sf::Text> create_text(const std::string &id, const std::string &text,
                                        sf::Vector2u screen_pos = sf::Vector2u(0, 0),
                                        sf::Vector2f scale = sf::Vector2f(1, 1),
                                        sf::Color color = sf::Color::White);

    /**
     * Returns the text identified by id
     *
     * @param id
     * @return std::weak_ptr<sf::Text>
     */
    std::weak_ptr<sf::Text> get_text(const std::string &id);

    /**
     * Fixes text to the right of the screen, with some padding
     *
     * @param st
     * @param maxChars
     * @return std::string
     */
    static std::string fix_text_to_right(const std::string &st, const int maxChars);
};
