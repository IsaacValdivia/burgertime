#include "GUI.hpp"
#include "Constants.hpp"

GUI::GUI()
{
    if (!font.loadFromFile(FONT_FILE))
    {
        // TODO: error
    }
}

GUI::~GUI()
{
}

GUI &GUI::get()
{
    static GUI instance;
    return instance;
}

std::weak_ptr<sf::Text> GUI::createText(const std::string &id, const std::string &text, sf::Vector2u screenPos, 
    sf::Vector2f scale, sf::Color color)
{
    auto textObj = std::make_shared<sf::Text>();
    guiTexts[id] = textObj;

    textObj->setFillColor(color);
    textObj->setScale(scale);
    textObj->setString(text);
    textObj->setFont(font);
    textObj->setPosition(screenPos.x * HORIZONTAL_DIVISIONS, screenPos.y * VERTICAL_DIVISIONS);

    return textObj;
}

std::weak_ptr<sf::Text> GUI::getText(const std::string &id)
{
    if (guiTexts.find(id) != guiTexts.end())
    {
        return guiTexts[id];
    }
    else
    {
        // TODO: exception
    }
}
