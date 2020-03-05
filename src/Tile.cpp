#include "Tile.hpp"

Tile::Tile() : col(0), row(0), content(EMPTY) {};

Tile::Tile(uint8_t _col, uint8_t _row, char _content) : col(_col), row(_row), content(_content) {};

Tile& Tile::operator=(const Tile& other) {
	row = other.row;
	col = other.col;
	content = other.content;
}

bool Tile::isEmpty() {
	return content == EMPTY;
}

bool Tile::isFloor() {
	return content == FLOOR || content == ENTRY_N_FLOOR;
}

bool Tile::isConnector() {
	return content == GO_UP || content == GO_DOWN || content == GO_BOTH ||
			content == ENTRY_N_UP || content == ENTRY_N_DOWN || content == ENTRY_N_BOTH;
}

bool Tile::isStairs() {
	return content == STAIRS;
}
