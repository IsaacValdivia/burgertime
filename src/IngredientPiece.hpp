#pragma once

#include <cstdint>
#include "Entity.hpp"

class IngredientPiece : public Entity {
private:
    bool falling;
    
public:
    bool stepped;
    uint8_t row;
    uint8_t col;

    IngredientPiece();
    IngredientPiece(const sf::Vector2f& _init_pos, BT_sprites::Sprite _init_sprite, uint8_t _row, uint8_t _col);

    void update(float delta_t) override;

    void step();
    void drop();
    void land();
};
