#pragma once

#include <SFML/Graphics.hpp>

class Actor : public sf::Sprite
{
public:
    virtual void update() = 0;
};
