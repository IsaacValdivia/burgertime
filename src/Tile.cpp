#include "Tile.hpp"

StaticTexture Tile::floor_tex(FLOOR_PATH);
StaticTexture Tile::go_up_both_tex(GO_UP_BOTH_PATH);
// StaticTexture Tile::go_up_both_tex("img/red_square.png");
StaticTexture Tile::go_down_tex(GO_DOWN_PATH);
StaticTexture Tile::stairs_tex(STAIRS_PATH);
// StaticTexture Tile::stairs_tex("img/stairs.png");
StaticTexture Tile::left_basket_tex(LEFT_BASKET_PATH);
StaticTexture Tile::mid_basket_tex(MID_BASKET_PATH);
StaticTexture Tile::right_basket_tex(RIGHT_BASKET_PATH);

Tile::Tile(const float _x, const float _y, const uint8_t _row, const uint8_t _col,
           const Type _content, const bool _left)
    : col(_col), row(_row), height(3), content(_content), left(_left),
      shape(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT)) {

    shape.setPosition(_x, _y);
    if (this->is_floor()) {
        shape.setTexture(&floor_tex.getTexture());
    }
    else if (this->is_go_up() || this->is_go_both()) {
        shape.setTexture(&go_up_both_tex.getTexture());
        if (_left) {
            shape.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
        }
        else {
            shape.setTextureRect(sf::IntRect(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
        }
    }
    else if (this->is_go_down()) {
        shape.setTexture(&go_down_tex.getTexture());
    }
    else if (this->is_stairs()) {
        height = 0;
        shape.setTexture(&stairs_tex.getTexture());
        if (_left) {
            shape.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
        }
        else {
            shape.setTextureRect(sf::IntRect(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
        }
    }
    else if (this->is_basket()) {
        height = 2;
        shape.setTexture(&mid_basket_tex.getTexture());
    }
    else if (this->is_basket_edge()) {
        if (_left) {
            shape.setTexture(&left_basket_tex.getTexture());
        }
        else {
            shape.setTexture(&right_basket_tex.getTexture());
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

#if false
    auto collision_shape = shape.getGlobalBounds();
    sf::RectangleShape drawShape;
    drawShape.setOutlineColor(sf::Color::Red);
    drawShape.setFillColor(sf::Color::Transparent);
    drawShape.setOutlineThickness(0.8);
    drawShape.setPosition(collision_shape.left, collision_shape.top);
    drawShape.setSize(sf::Vector2f(collision_shape.width, collision_shape.height));
    target.draw(drawShape, states);
#endif
}

Tile &Tile::operator=(const Tile &other) {
    row = other.row;
    col = other.col;
    content = other.content;
    height = other.height;
    shape = other.shape;

    return *this;
}

unsigned int Tile::get_height() const {
    return height;
}


sf::Vector2f Tile::get_position() const {
    return shape.getPosition();
}

char Tile::get_row() const {
    return row;
}

char Tile::get_col() const {
    return col;
}

void Tile::set_row(const uint8_t _row) {
    row = _row;
}

void Tile::set_col(const uint8_t _col) {
    col = _col;
}


bool Tile::is_empty() const {
    return content == EMPTY;
}

bool Tile::is_floor() const {
    return content == FLOOR;
}

bool Tile::is_go_up() const {
    return content == GO_UP;
}

bool Tile::is_go_down() const {
    return content == GO_DOWN;
}

bool Tile::is_go_both() const {
    return content == GO_BOTH;
}

bool Tile::is_connector() const {
    return content == GO_UP || content == GO_DOWN || content == GO_BOTH;
}

bool Tile::is_stairs() const {
    return content == STAIRS;
}

bool Tile::is_basket() const {
    return content == BASKET;
}

bool Tile::is_basket_edge() const {
    return content == BASKET_EDGE;
}

bool Tile::is_steppable_hor() const {
    return this->is_floor() || this->is_connector();
}

bool Tile::is_steppable_vert() const {
    return this->is_stairs() || this->is_connector();
}

bool Tile::is_steppable_vert_left() const {
    return this->is_steppable_vert() && left;
}

bool Tile::is_steppable_vert_right() const {
    return this->is_steppable_vert() && !left;
}
