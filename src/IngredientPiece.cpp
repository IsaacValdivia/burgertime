#include "IngredientPiece.hpp"

// IngredientPiece::IngredientPiece() : falling(false), row(0), col(0) {

// }

IngredientPiece::IngredientPiece(const sf::Vector2f& _init_pos, BT_sprites::Sprite _init_sprite, uint8_t _row, uint8_t _col) : Entity(_init_pos, _init_sprite), falling(false), stepped(false), row(_row), col(_col) {
    this->sprite.setScale(2,2);
    // TO_DO: Funcionara?
}

void IngredientPiece::update(float delta_t) {
    // UPDATE IS ONLY CALLED WHEN INGREDIENT IS FALLING
    this->sprite.move(0,60 * delta_t);
}

void IngredientPiece::step() {
    stepped = true;
}

bool IngredientPiece::isStepped() {
    return stepped;
}

void IngredientPiece::move() {
    this->sprite.move(0, y_movement);
}

void IngredientPiece::drop() {
    falling = true;
}

void IngredientPiece::land() {
    falling = false;
}
