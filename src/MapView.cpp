#include "MapView.hpp"

using namespace sf;

sf::Texture MapView::floor_texture;
sf::Texture MapView::go_up_texture;
sf::Texture MapView::go_down_texture;
sf::Texture MapView::stairs_texture;

sf::RectangleShape MapView::floor(Vector2f(TILE_WIDTH, TILE_HEIGHT));

sf::RectangleShape MapView::go_down(Vector2f(TILE_WIDTH, TILE_HEIGHT));

sf::RectangleShape MapView::go_up_left(Vector2f(TILE_WIDTH, TILE_HEIGHT));
sf::RectangleShape MapView::go_up_right(Vector2f(TILE_WIDTH, TILE_HEIGHT));

sf::RectangleShape MapView::stairs_left(Vector2f(TILE_WIDTH, TILE_HEIGHT));
sf::RectangleShape MapView::stairs_right(Vector2f(TILE_WIDTH, TILE_HEIGHT));

MapView::MapView(Map *_map)
{
    floor_texture.loadFromFile("./img/floor.png");
    go_up_texture.loadFromFile("./img/go_up.png");
    go_down_texture.loadFromFile("./img/go_down.png");
    stairs_texture.loadFromFile("./img/stairs.png");

    floor.setTexture(&floor_texture);

    go_down.setTexture(&go_down_texture);

    go_up_left.setTexture(&go_up_texture);
    go_up_right.setTexture(&go_up_texture);

    go_up_left.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
    go_up_right.setTextureRect(sf::IntRect(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));

    stairs_left.setTexture(&stairs_texture);
    stairs_right.setTexture(&stairs_texture);

    stairs_left.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
    stairs_right.setTextureRect(sf::IntRect(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));

    map = _map;
}

void MapView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    // unsigned int dimX = 1000;
    // unsigned int dimY = 1000;

    // sf::Vector2f tile_size(4.0f, 4.0f);

    // sf::RenderWindow window(sf::VideoMode(dimX, dimY), "Burgertime");
    // RectangleShape floor(Vector2f(TILE_DIM, TILE_DIM));

    // window.clear();

    unsigned int i = 0, j;
    for (auto &row : map->data)
    {
        j = 0;
        bool double_placed = false;
        for (auto &tile : row)
        {
            if (tile.isFloor())
            {
                floor.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(floor, states);

                double_placed = false;
            }
            else if ((tile.isGoUp() || tile.isGoBoth()) && !double_placed)
            {
                go_up_left.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(go_up_left, states);
                go_up_right.setPosition(SIDE_MARGINS + (j+1) * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(go_up_right, states);

                double_placed = true;
            }
            else if (tile.isGoDown())
            {
                go_down.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(go_down, states);

                double_placed = false;
            }
            else if (tile.isStairs() && !double_placed)
            {
                stairs_left.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(stairs_left, states);
                stairs_right.setPosition(SIDE_MARGINS + (j+1) * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(stairs_right, states);

                double_placed = true;
            }
            else {
                double_placed = false;
            }

            ++j;
        }

        ++i;
    }
}

std::vector<Tile> MapView::player_on_tiles(const sf::Vector2f position, const sf::Vector2f scale) const {
    std::vector<Tile> tiles;

    float left_edge = position.x;
    float right_edge = position.x + scale.x;
    float upper_edge = position.y;
    float lower_edge = position.y + scale.y;

    // Check left_edge
    unsigned short horizontal_tile_1 = (left_edge - SIDE_MARGINS) / TILE_WIDTH;

    // Check right_edge
    unsigned short horizontal_tile_2 = (right_edge - SIDE_MARGINS) / TILE_WIDTH;

    // Check upper_edge
    unsigned short vertical_tile_1 = (upper_edge - UPPER_MARGIN) / TILE_HEIGHT;

    // Check lower_edge
    unsigned short vertical_tile_2 = (lower_edge - UPPER_MARGIN) / TILE_HEIGHT;
    
    tiles.push_back(map->data[horizontal_tile_1][vertical_tile_1]);
    bool c1, c2;

    if (horizontal_tile_1 != horizontal_tile_2) {
        tiles.push_back(map->data[horizontal_tile_2][vertical_tile_1]);
        c1 = true;
    }

    if (vertical_tile_1 != vertical_tile_2) {
        tiles.push_back(map->data[horizontal_tile_1][vertical_tile_2]);
        c2 = true;
    }

    if (c1 && c2) {
        tiles.push_back(map->data[horizontal_tile_2][vertical_tile_2]);
    }

    return tiles;
}

bool MapView::player_can_move(float &x, float &y, const sf::Sprite& player) const {
    sf::Vector2f cur_pos = player.getPosition();
    sf::Vector2f player_size = player.getScale();

    std::vector<Tile> tiles_of_player = player_on_tiles(cur_pos, player_size);

    bool horizontal_mov = x != 0;
    bool up, right;

    if (horizontal_mov) {
        right = x > 0;
    }
    else {
        up = x < 0;
    }

    bool can_move = false;
    unsigned int i = 0;
    while (!can_move && i < tiles_of_player.size()) {
        Tile &t = tiles_of_player[i];
        uint8_t row = t.row, col = t.col;
        if (t.isFloor()) {
            if (horizontal_mov) {
                if (right) {
                    // Player tries to go right
                    can_move = col < (Map::MAX_COLS - 1) && map->data[row][col+1].isSteppableHor();
                }
                else {
                    // Player tries to go left
                    can_move = col > 0 && map->data[row][col-1].isSteppableHor();
                }
            }
            else {
                // Vertical movement is not possible on floor
            }
        }
        // TO_DO: RESTO DE TIPOS DE TILE

        ++i;
    }

    return can_move;
}
