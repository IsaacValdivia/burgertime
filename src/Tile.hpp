#pragma once

#include "StaticTexture.hpp"

#include <cstdint>
#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable {
public:
    static constexpr float TILE_WIDTH = 16.0;
    static constexpr float TILE_HEIGHT = 16.0;

    // Tile codes for regular, inner tiles
    enum Type : char {
        FLOOR = '_',
        GO_UP = '^',
        GO_DOWN = 'v',
        GO_BOTH = '|',
        STAIRS = '#',
        BASKET_EDGE = '-',
        BASKET = 'u',
        // Empty tile (background)
        EMPTY = ' '
    };

private:
    static constexpr auto FLOOR_PATH = "img/floor.png";
    static constexpr auto GO_UP_BOTH_PATH = "img/go_up.png";
    static constexpr auto GO_DOWN_PATH = "img/go_down.png";
    static constexpr auto STAIRS_PATH = "img/stairs.png";
    static constexpr auto LEFT_BASKET_PATH = "img/left_basket.png";
    static constexpr auto MID_BASKET_PATH = "img/mid_basket.png";
    static constexpr auto RIGHT_BASKET_PATH = "img/right_basket.png";

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

    Type content;

    sf::RectangleShape shape;

public:
    /**
     * @brief Construct a new Tile object
     *
     * @param _x x position
     * @param _y y position
     * @param _row row of the tile
     * @param _col col of the tile
     * @param _content content inside the tile
     * @param _right relevant if the tile is stairs, go up, go both or basket
     */
    Tile(const float _x, const float _y, const uint8_t _row,
         const uint8_t _col, const Type _content, const bool _right);

    /**
     * @brief Construct a new Tile object
     *
     * @param other tile to copy from
     */
    Tile(const Tile &other);

    /**
     * @brief = Operator for tiles, copies attributes
     *
     * @param other tile to copy
     * @return Tile&
     */
    Tile &operator=(const Tile &other);

    /**
     * @brief A tile is lower than other if so are its row and col
     *
     * @param other tile to compare
     * @return Tile&
     */
    bool operator<(const Tile &other) const;

    /**
     * @brief A tile is equal to other if so are its row and col
     *
     * @param other tile to compare
     * @return Tile&
     */
    bool operator==(const Tile &other) const;

    /**
     * @brief Draws a tile on screen
     *
     * @param target target to draw on
     * @param states states of drawable
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * Returns the height of the tile
     *
     * @return unsigned int height
     */
    unsigned int get_height() const;

    /**
     * Returns the position in world coordinates of the tile
     *
     * @return sf::Vector2f vector_position
     */
    sf::Vector2f get_position() const;

    /**
     * Returns the row of the tile
     *
     * @return char row
     */
    char get_row() const;

    /**
     * Returns the column of the tile
     *
     * @return char column
     */
    char get_col() const;

    /**
     * @brief Returns true if the tile is empty
     *
     * @return true
     * @return false
     */
    bool is_empty() const;

    /**
     * @brief Returns true if the tile is floor
     *
     * @return true
     * @return false
     */
    bool is_floor() const;

    /**
     * @brief Returns true if the tile is an upwards stair
     *
     * @return true
     * @return false
     */
    bool is_go_up() const;

    /**
     * @brief Returns true if the tile is a downwards stair
     *
     * @return true
     * @return false
     */
    bool is_go_down() const;

    /**
     * @brief Returns true if the tile is a up/downwards stair
     *
     * @return true
     * @return false
     */
    bool is_go_both() const;

    /**
     * @brief Returns true if the tile is some kind of floor with stairs
     *
     * @return true
     * @return false
     */
    bool is_connector() const;

    /**
     * @brief Returns true if the tile is stairs
     *
     * @return true
     * @return false
     */
    bool is_stairs() const;

    /**
     * @brief Returns true if the tile is a basket edge
     *
     * @return true
     * @return false
     */
    bool is_basket_edge() const;

    /**
     * @brief Returns true if the tile is a basket mid
     *
     * @return true
     * @return false
     */
    bool is_basket() const;

    /**
     * @brief Returns true if the tile is steppable horizontally
     *
     * @return true
     * @return false
     */
    bool is_steppable_hor() const;

    /**
     * @brief Returns true if the tile is steppable vertically
     *
     * @return true
     * @return false
     */
    bool is_steppable_vert() const;
};
