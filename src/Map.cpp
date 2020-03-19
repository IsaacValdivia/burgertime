#include "Map.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void Map::fill_tiles(const vector<string> &map_data) {
    unsigned int i = 0, j;
    bool double_placed = false;
    for (auto& row : map_data) {
        j = 0;
        for (auto& content : row) {
            float x = SIDE_MARGINS + j * Tile::TILE_WIDTH;
            float y = UPPER_MARGIN + i * Tile::TILE_HEIGHT;
            if (content == Tile::STAIRS || content == Tile::GO_UP || content == Tile::GO_BOTH) {
                double_placed = !double_placed;
            }
            data[i][j] = Tile(x, y, i, j, content, double_placed);
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
        
        f.close();
        fill_tiles(rows);
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

std::vector<Tile> Map::player_on_tiles(const float bot_left_x, const float bot_right_x, const float bot_y) const
{
    std::vector<Tile> tiles;

    // Check left_edge
    size_t horizontal_tile_1 = (bot_left_x - (SIDE_MARGINS + 1)) / Tile::TILE_WIDTH;

    // Check right_edge
    size_t horizontal_tile_2 = (bot_right_x - (SIDE_MARGINS + 1)) / Tile::TILE_WIDTH;

    // Check upper_edge
    size_t vertical_tile = (bot_y - (UPPER_MARGIN + 1)) / Tile::TILE_HEIGHT;

    for (int h_i = horizontal_tile_1; h_i < horizontal_tile_2 + 1; ++h_i) {
        tiles.push_back(data[vertical_tile][h_i]);
    }

    return tiles;
}

bool Map::can_move_right(const Tile& t, float right_edge) const {
    // check if platform allows the movement
    if (t.isFloor() || t.isGoUp() || t.isGoDown() || t.isGoBoth()) {
        // if next tile also allows hor movement, true
        if (t.col < (MAX_COLS - 1) && data[t.row][t.col+1].isSteppableHor()) {
            return true;
        }
        // if end of tile has not been reached, true
        float tile_edge = t.shape.getPosition().x + Tile::TILE_WIDTH;
        if (right_edge < tile_edge /* - HOR_COLL_LOOKAHEAD_CORR */) {
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

bool Map::can_move_left(const Tile& t, float left_edge) const {
    // check if platform allows the movement
    if (t.isFloor() || t.isGoUp() || t.isGoDown() || t.isGoBoth()) {
        // if next tile also allows hor movement, true
        if (t.col > 0 && data[t.row][t.col-1].isSteppableHor()) {
            return true;
        }
        // if end of tile has not been reached, true
        float tile_edge = t.shape.getPosition().x;
        if (left_edge > tile_edge /* - HOR_COLL_LOOKAHEAD_CORR */) {
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

bool Map::can_move_up(const Tile& t, float top_edge) const {
    // check if platform allows the movement
    if (t.isStairs() || t.isGoUp() || t.isGoBoth() || t.isGoDown()) {
        // if next tile also allows hor movement, true
        if (t.row > 0 && data[t.row-1][t.col].isSteppableVert()) {
            return true;
        }
        // if end of tile has not been reached, true
        float tile_edge = t.shape.getPosition().y + 14;
        if (top_edge > tile_edge /* - HOR_COLL_LOOKAHEAD_CORR */) {
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

bool Map::can_move_down(const Tile& t, float bot_edge) const {
    // check if platform allows the movement
    if (t.isStairs() || t.isGoDown() || t.isGoBoth() || t.isGoUp()) {
        // if next tile also allows hor movement, true
        if (t.row < (MAX_ROWS - 1) && data[t.row+1][t.col].isSteppableVert()) {
            return true;
        }
        // if end of tile has not been reached, true
        float tile_edge = t.shape.getPosition().y + Tile::TILE_HEIGHT - 3;
        if (bot_edge < tile_edge /* - HOR_COLL_LOOKAHEAD_CORR */) {
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

/* float fix_x(float chef_center, float stairs_center) {
        return stairs_center - chef_center;
}*/

bool Map::player_can_move(float &x, float &y, const sf::Sprite& player) const {
    // float left_edge = player.getTransform().transformPoint(Vector2f(0, 0)).x;
    // float right_edge = player.getTransform().transformPoint(Vector2f(player.getSize().x, 0)).x;
    // float upper_edge = player.getTransform().transformPoint(Vector2f(0, 0)).y;
    // float lower_edge = player.getTransform().transformPoint(Vector2f(player.getSize().x, player.getSize().y)).y;


    float bot_left_x = player.getGlobalBounds().left + 10;
    float bot_right_x = player.getGlobalBounds().left + player.getGlobalBounds().width - 10;
    // float upper_edge = player.getGlobalBounds().top;
    float bot_y = player.getGlobalBounds().top + player.getGlobalBounds().height;

    // float left_edge = cur_pos.x - player_size.x / 2.0;
    // float right_edge = cur_pos.x + player_size.x / 2.0;
    // float upper_edge = cur_pos.y - player_size.y / 2.0;
    // float lower_edge = cur_pos.y + player_size.y / 2.0;

    std::vector<Tile> tiles_of_player = player_on_tiles(bot_left_x, bot_right_x, bot_y);

    bool horizontal_mov = x != 0;
    bool up = false, right = false;

    if (horizontal_mov) {
        right = x > 0;
    }
    else {
        up = y < 0;
    }
    if (horizontal_mov && right && can_move_right(tiles_of_player.back(), bot_right_x)) {
        y = ((tiles_of_player[0].shape.getPosition().y + Tile::TILE_HEIGHT) - 3) - bot_y;
        return true;
    } else if (horizontal_mov && !right && can_move_left(tiles_of_player.front(), bot_left_x)) {
        y = ((tiles_of_player[0].shape.getPosition().y + Tile::TILE_HEIGHT) - 3) - bot_y;
        return true;
    } else {
        short up_bot_count = 0;
        bool first_time = true;
        for (const auto &tile : tiles_of_player) {
            if (!horizontal_mov && up && can_move_up(tile, bot_y)) {
                if (first_time) {
                    x = (tile.shape.getPosition().x + Tile::TILE_WIDTH) - ((bot_right_x + bot_left_x) / 2.0);
                    first_time = false;
                }
                ++up_bot_count;
            } else if (!horizontal_mov && !up && can_move_down(tile, bot_y)) {
                if (first_time) {
                    x = (tile.shape.getPosition().x + Tile::TILE_WIDTH) - ((bot_right_x + bot_left_x) / 2.0);
                    first_time = false;
                }
                ++up_bot_count;
            }
        }

        if (up_bot_count == 2) {
            return true;
        }
    }

    // etc

    // bool can_move = false;
    // unsigned int i = 0;
    // while (!can_move && i < tiles_of_player.size()) {
    //     Tile &t = tiles_of_player[i];
    //     uint8_t row = t.row, col = t.col;
    //     if (t.isFloor()) {
    //         if (horizontal_mov) {
    //             if (right) {
    //                 // Player tries to go right
    //                 can_move = can_move_right(t, bot_right_x);
    //             }
    //             else {
    //                 // Player tries to go left
    //                 can_move = col > 0 && data[row][col-1].isSteppableHor();
    //             }
    //         }
    //         else {
    //             // Vertical movement is not possible on floor
    //         }
    //     }
    //     // TO_DO: RESTO DE TIPOS DE TILE
    //     ++i;
    // }

    return false;
}
