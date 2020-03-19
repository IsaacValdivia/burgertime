#include "Tile.hpp"

StaticTexture Tile::floor_tex(FLOOR_PATH);
StaticTexture Tile::go_up_both_tex(GO_UP_BOTH_PATH);
StaticTexture Tile::go_down_tex(GO_DOWN_PATH);
StaticTexture Tile::stairs_tex(STAIRS_PATH);

Tile::Tile() : col(0), row(0), content(EMPTY) {
	shape.setPosition(0.0, 0.0);
};

Tile::Tile(float _x, float _y, uint8_t _col, uint8_t _row, char _content) : col(_col), row(_row), content(_content) {
	shape.setPosition(_x, _y);
	if (this->isFloor()) {
		shape.setTexture(&floor_tex.tex);
	} 
	else if (this->isGoUp() || this->isGoBoth()) {
		shape.setTexture(&go_up_both_tex.tex);
	} 
	else if (this->isGoDown()) {
		shape.setTexture(&go_down_tex.tex);
	} 
	else if (this->isStairs()) {
		shape.setTexture(&stairs_tex.tex);
	}
};

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(shape, states);
}

void Tile::operator=(const Tile& other) {
	row = other.row;
	col = other.col;
	content = other.content;
}

bool Tile::isEmpty() const {
	return content == EMPTY;
}

bool Tile::isFloor() const {
	return content == FLOOR;
}

bool Tile::isGoUp() const {
	return content == GO_UP;
}

bool Tile::isGoDown() const {
	return content == GO_DOWN;
}

bool Tile::isGoBoth() const {
	return content == GO_BOTH;
}

bool Tile::isConnector() const {
	return content == GO_UP || content == GO_DOWN || content == GO_BOTH;
}

bool Tile::isStairs() const {
	return content == STAIRS;
}

bool Tile::isSteppableHor() const {
	return this->isFloor() || this->isConnector();
}
