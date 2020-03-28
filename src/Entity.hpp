#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
protected:
    float acc_delta_t;

public:
    virtual void update(float delta_t) {};

    virtual sf::FloatRect getCollisionShape() const = 0;

    virtual bool intersectsWith(const Entity &entity) const;
};
