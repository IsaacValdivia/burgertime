#include "GUI.hpp"

#include "Constants.hpp"

GUI::GUI() {
    if (!font.loadFromFile(FONT_FILE)) {
        throw std::runtime_error("Error loading font file");
    }
}

GUI::~GUI() {}

GUI &GUI::get() {
    static GUI instance;
    return instance;
}

std::weak_ptr<sf::Text> GUI::create_text(const std::string &id,
        const std::string &text,
        sf::Vector2u screen_pos,
        sf::Vector2f scale, sf::Color color) {

    auto text_obj = std::make_shared<sf::Text>();
    gui_texts[id] = text_obj;

    text_obj->setFillColor(color);
    text_obj->setScale(scale);
    text_obj->setString(text);
    text_obj->setFont(font);
    text_obj->setPosition(screen_pos.x * HORIZONTAL_DIVISIONS, screen_pos.y * VERTICAL_DIVISIONS);

    return text_obj;
}

void GUI::delete_text(const std::string &id) {
    gui_texts.erase(id);
}


std::weak_ptr<sf::Text> GUI::get_text(const std::string &id) {
    if (gui_texts.find(id) != gui_texts.end()) {
        return gui_texts[id];
    }
    else {
        throw std::runtime_error("GUI text not found");
    }
}

std::string GUI::fix_text_to_right(const std::string &st, const int max_chars) {
    std::string white_space(" ");

    for (uint8_t j = 0; j < max_chars - st.length(); ++j) {
        white_space += " ";
    }

    return white_space + st;
}
