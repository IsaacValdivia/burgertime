#include "Ingredient.hpp"

Ingredient::Ingredient() : col(0), row(0), type(Type::NONE) {};

Ingredient::Ingredient(uint8_t _col, uint8_t _row, Type _type) : col(_col), row(_row), type(_type) {};

void Ingredient::operator=(const Ingredient& other) {
	row = other.row;
	col = other.col;
	type = other.type;
}