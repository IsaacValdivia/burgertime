#pragma once

#include <SFML/Graphics.hpp>

class StaticTexture {
public:
    sf::Texture tex;
    StaticTexture(std::string path);
};