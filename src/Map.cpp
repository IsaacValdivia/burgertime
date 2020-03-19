#include "Map.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void Map::fill_tiles(const vector<string> &map_data) {
    unsigned int i = 0, j;
    for (auto& row : map_data) {
        j = 0;
        for (auto& content : row) {
            float x = SIDE_MARGINS + j * TILE_WIDTH;
            float y = UPPER_MARGIN + i * TILE_HEIGHT;
            data[i][j] = Tile(x, y, i, j, content);
            ++j;
        }
        ++i;
    }
}

Map::Map(const vector<string> &map_data) {
    fill_tiles(map_data);
};

Map::Map(const string &filename) {
    ifstream f;
    f.open(filename);

    if (f.is_open()) {
        vector<string> rows;
        char row_aux[MAX_COLS + 1];
        string row;
        while (!f.eof()) {
            f.getline(row_aux, MAX_COLS + 1);
            row = row_aux;
            int s = row.size();
            if (s != MAX_COLS) {
                throw runtime_error("Rows can only have " + to_string(MAX_COLS) + " tiles");
            }
            rows.push_back(row);
        }
        
        fill_tiles(rows);
        f.close();
    } else {
        throw runtime_error("File " + filename + " could not be found");
    }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto& row : data) {
        for (auto& tile : row) {
            target.draw(tile, states);
        }
    }
}

std::vector<Tile> Map::player_on_tiles(const float left_edge, const float right_edge, const float upper_edge, const float lower_edge) const {
    std::vector<Tile> tiles;

    // Check left_edge
    unsigned short horizontal_tile_1 = (left_edge - SIDE_MARGINS) / TILE_WIDTH;

    // Check right_edge
    unsigned short horizontal_tile_2 = (right_edge - SIDE_MARGINS) / TILE_WIDTH;

    // Check upper_edge
    unsigned short vertical_tile_1 = (upper_edge - UPPER_MARGIN) / TILE_HEIGHT;

    // Check lower_edge
    unsigned short vertical_tile_2 = (lower_edge - UPPER_MARGIN) / TILE_HEIGHT;
    
    tiles.push_back(data[horizontal_tile_1][vertical_tile_1]);
    bool c1, c2;

    if (horizontal_tile_1 != horizontal_tile_2) {
        tiles.push_back(data[horizontal_tile_2][vertical_tile_1]);
        c1 = true;
    }

    if (vertical_tile_1 != vertical_tile_2) {
        tiles.push_back(data[horizontal_tile_1][vertical_tile_2]);
        c2 = true;
    }

    if (c1 && c2) {
        tiles.push_back(data[horizontal_tile_2][vertical_tile_2]);
    }

    return tiles;
}

bool Map::can_move_right(const Tile& t, float right_edge) const {
    // check if platform allows the movement
    if (t.isFloor() || t.isGoUp() || t.isGoDown()) {
        // if next tile also allows hor movement, true
        if (t.col < (MAX_COLS - 1) && data[t.row][t.col+1].isSteppableHor()) {
            return true;
        }
        // if end of tile has not been reached, true
        float tile_edge = t.shape.getPosition().x + TILE_WIDTH;
        if (right_edge < tile_edge - HOR_COLL_LOOKAHEAD_CORR) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Map::player_can_move(float &x, float &y, const sf::Sprite& player) const {
    sf::Vector2f cur_pos = player.getPosition();
    sf::Vector2f player_size = player.getScale();

    float left_edge = cur_pos.x;
    float right_edge = cur_pos.x + player_size.x;
    float upper_edge = cur_pos.y;
    float lower_edge = cur_pos.y + player_size.y;

    std::vector<Tile> tiles_of_player = player_on_tiles(left_edge, right_edge, upper_edge, lower_edge);

    bool horizontal_mov = x != 0;
    bool up = false, right = false;

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
                    can_move = can_move_right(t, right_edge);
                }
                else {
                    // Player tries to go left
                    can_move = col > 0 && data[row][col-1].isSteppableHor();
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
