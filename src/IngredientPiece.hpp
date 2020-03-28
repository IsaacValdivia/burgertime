#pragma once

#include <cstdint>
#include "Entity.hpp"

class IngredientPiece : public Entity {
private:
    bool falling;

    static constexpr auto y_movement = 1.2;
    
public:
    bool stepped;
    uint8_t row;
    uint8_t col;

    IngredientPiece(const sf::Vector2f& _init_pos, BT_sprites::Sprite _init_sprite, uint8_t _row, uint8_t _col);

    void update(float delta_t) override;

    bool isStepped() const;
    void step();
    void move();
    void drop();
    void land();

    friend class Ingredient;
};
