#pragma once

#include <SFML/Graphics.hpp>

class Updrawable : public sf::Drawable {
protected:
    float acc_delta_t;

public:
    virtual void update(float delta_t) = 0;
};
