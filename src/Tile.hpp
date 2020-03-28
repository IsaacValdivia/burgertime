#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>

#include "StaticTexture.hpp"

class Tile : public sf::Drawable {
private:
    static constexpr auto FLOOR_PATH = "img/floor.png";
    static constexpr auto GO_UP_BOTH_PATH = "img/go_up.png";
    static constexpr auto GO_DOWN_PATH = "img/go_down.png";
    static constexpr auto STAIRS_PATH = "img/stairs.png";
    static constexpr auto LEFT_BASKET_PATH = "img/left_basket.png";
    static constexpr auto MID_BASKET_PATH = "img/mid_basket.png";
    static constexpr auto RIGHT_BASKET_PATH = "img/right_basket.png";

public:    
    // Tile codes for regular, inner tiles
    static const char FLOOR = '_';
    static const char GO_UP = '^';
    static const char GO_DOWN = 'v';
    static const char GO_BOTH = '|';
    static const char STAIRS = '#';
    static const char BASKET_EDGE = '-';
    static const char BASKET = 'u';
    // Empty tile (background)
    static const char EMPTY = ' ';

    static constexpr float TILE_WIDTH = 16.0;
    static constexpr float TILE_HEIGHT = 16.0;

    static StaticTexture floor_tex;
    static StaticTexture go_up_both_tex;
    static StaticTexture go_down_tex;
    static StaticTexture stairs_tex;
    static StaticTexture left_basket_tex;
    static StaticTexture mid_basket_tex;
    static StaticTexture right_basket_tex;

    uint8_t col;
    uint8_t row;
    unsigned int height;
    char content;
    sf::RectangleShape shape;

    Tile();
    Tile(float _x, float _y, uint8_t _row, uint8_t _col, char _content, bool _right);
    Tile(const Tile &other);

    Tile& operator=(const Tile& other);

    bool operator<(const Tile& other) const;

    bool operator==(const Tile &other) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool isEmpty() const;
    bool isFloor() const;
    bool isGoUp() const;
    bool isGoDown() const;
    bool isGoBoth() const;
    bool isConnector() const;
    bool isStairs() const;
    bool isBasketEdge() const;
    bool isBasket() const;
    bool isSteppableHor() const;
    bool isSteppableVert() const;
};
