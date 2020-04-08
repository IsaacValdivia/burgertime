#include "Tile.hpp"

StaticTexture Tile::floor_tex(FLOOR_PATH);
StaticTexture Tile::go_up_both_tex(GO_UP_BOTH_PATH);
StaticTexture Tile::go_down_tex(GO_DOWN_PATH);
StaticTexture Tile::stairs_tex(STAIRS_PATH);
StaticTexture Tile::left_basket_tex(LEFT_BASKET_PATH);
StaticTexture Tile::mid_basket_tex(MID_BASKET_PATH);
StaticTexture Tile::right_basket_tex(RIGHT_BASKET_PATH);

Tile::Tile() : col(0), row(0), height(0), content(EMPTY) {
    shape.setPosition(0.0, 0.0);
};

Tile::Tile(float _x, float _y, uint8_t _row, uint8_t _col, char _content, bool _left) : col(_col), row(_row), height(3), content(_content), shape(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT)) {
    shape.setPosition(_x, _y);
    if (this->isFloor()) {
        shape.setTexture(&floor_tex.tex);
    }
    else if (this->isGoUp() || this->isGoBoth()) {
        shape.setTexture(&go_up_both_tex.tex);
        if (_left) {
            shape.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
        }
        else {
            shape.setTextureRect(sf::IntRect(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
        }
    }
    else if (this->isGoDown()) {
        shape.setTexture(&go_down_tex.tex);
    }
    else if (this->isStairs()) {
        height = 0;
        shape.setTexture(&stairs_tex.tex);
        if (_left) {
            shape.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
        }
        else {
            shape.setTextureRect(sf::IntRect(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
        }
    }
    else if (this->isBasket()) {
        height = 2;
        shape.setTexture(&mid_basket_tex.tex);
    }
    else if (this->isBasketEdge()) {
        if (_left) {
            shape.setTexture(&left_basket_tex.tex);
        }
        else {
            shape.setTexture(&right_basket_tex.tex);
        }
    }
    else {
        shape.setFillColor(sf::Color::Black);
    }
};

Tile::Tile(const Tile &other) {
    row = other.row;
    col = other.col;
    content = other.content;
    shape = other.shape;
}

bool Tile::operator<(const Tile &other) const {
    return col < other.col && row < other.row;
}

bool Tile::operator==(const Tile &other) const {
    return col == other.col && row == other.row;
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(shape, states);
}

Tile &Tile::operator=(const Tile &other) {
    row = other.row;
    col = other.col;
    content = other.content;
    shape = other.shape;

    return *this;
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

bool Tile::is_connector() const {
    return content == GO_UP || content == GO_DOWN || content == GO_BOTH;
}

bool Tile::isStairs() const {
    return content == STAIRS;
}

bool Tile::isBasket() const {
    return content == BASKET;
}

bool Tile::isBasketEdge() const {
    return content == BASKET_EDGE;
}

bool Tile::isSteppableHor() const {
    return this->isFloor() || this->is_connector();
}

bool Tile::isSteppableVert() const {
    return this->isStairs() || this->is_connector();
}
