#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
protected:
    float acc_delta_t; // Accumulated delta t field

public:
    Entity();

    /**
     * @brief Main control function, to be implemented
     *
     * @param delta_t
     */
    virtual void update(float delta_t) {};

    /**
     * @brief Get the collision shape object, to be implemented
     *
     * @return sf::FloatRect
     */
    virtual sf::FloatRect get_collision_shape() const = 0;

    /**
     * @brief Checks whether both entities intersect, to be implemented
     *
     * @param entity
     * @return true
     * @return false
     */
    virtual bool intersects_with(const Entity &entity) const;
};
