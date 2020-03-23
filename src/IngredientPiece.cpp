#include "IngredientPiece.hpp"

// IngredientPiece::IngredientPiece() : falling(false), row(0), col(0) {

// }

IngredientPiece::IngredientPiece(const sf::Vector2f& _init_pos, BT_sprites::Sprite _init_sprite, uint8_t _row, uint8_t _col) : Entity(_init_pos, _init_sprite), falling(false), row(_row), col(_col) {
    this->sprite.setScale(2,2);
    // TO_DO: Funcionara?
}

void IngredientPiece::update(float delta_t) {
    if (falling) {
        // TO_DO: Transformar, mover hacia abajo
    }
}

void IngredientPiece::drop() {
    falling = true;
}
