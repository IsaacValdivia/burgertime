#pragma once

#include <SFML/Graphics.hpp>

class StaticTexture {
public:
    sf::Texture tex;
    StaticTexture(const std::string &path);
};