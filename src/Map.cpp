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

std::vector<const Tile *> Map::actorOnTiles(const sf::FloatRect& collisionShape) const
{
    float bot_left_x = collisionShape.left;
    float bot_right_x = collisionShape.left + collisionShape.width;
    float bot_y = collisionShape.top + collisionShape.height;

    std::vector<const Tile *> tiles;

    // Check left_edge
    size_t horizontal_tile_1 = (bot_left_x - (SIDE_MARGINS + 1)) / Tile::TILE_WIDTH;

    // Check right_edge
    size_t horizontal_tile_2 = (bot_right_x - (SIDE_MARGINS + 1)) / Tile::TILE_WIDTH;

    // Check upper_edge
    size_t vertical_tile = (bot_y - (UPPER_MARGIN + 1)) / Tile::TILE_HEIGHT;

    for (int h_i = horizontal_tile_1; h_i < horizontal_tile_2 + 1; ++h_i) {
        if (data[vertical_tile][h_i].content != Tile::EMPTY) {
            tiles.push_back(&data[vertical_tile][h_i]);
        }
    }

    return tiles;
}


std::vector<const Tile *> Map::actorOnTiles(const Actor &actor) const
{
    auto collisionShape = actor.getCollisionShape();

    return actorOnTiles(collisionShape);
}

bool Map::horizontal_platform_check(const Tile &t) const {
    return t.isFloor() || t.isGoUp() || t.isGoDown() || t.isGoBoth();
}

bool Map::vertical_platform_check(const Tile &t) const {
    return t.isStairs() || t.isGoUp() || t.isGoDown() || t.isGoBoth();
}

bool Map::right_platform_check(const Tile &t) const {
    return t.col < (MAX_COLS - 1) && data[t.row][t.col+1].isSteppableHor();
}

bool Map::left_platform_check(const Tile &t) const {
    return t.col > 0 && data[t.row][t.col-1].isSteppableHor();
}

bool Map::up_platform_check(const Tile &t) const {
    return t.row > 0 && data[t.row-1][t.col].isSteppableVert();
}

bool Map::down_platform_check(const Tile &t) const {
    return t.row < (MAX_ROWS - 1) && data[t.row+1][t.col].isSteppableVert();
}

bool Map::can_move_right(const Tile &t) const {
    // check if platform allows the movement, and also right platform
    return horizontal_platform_check(t) && right_platform_check(t);
}

bool Map::can_move_left(const Tile &t) const {
    // check if platform allows the movement, and also left platform
    return horizontal_platform_check(t) && left_platform_check(t);
}

bool Map::can_move_up(const Tile &t) const {
    // check if platform allows the movement, and also top platform
    return vertical_platform_check(t) && up_platform_check(t);
}

bool Map::can_move_down(const Tile &t) const {
    // check if platform allows the movement, and also bottom platform
    return vertical_platform_check(t) && down_platform_check(t);
}

bool Map::can_move_right(const Tile& t, float right_edge) const {
    // check if platform allows the movement
    if (horizontal_platform_check(t)) {
        // if next tile also allows hor movement, true
        if (right_platform_check(t)) {
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
    if (horizontal_platform_check(t)) {
        // if next tile also allows hor movement, true
        if (left_platform_check(t)) {
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
    if (vertical_platform_check(t)) {
        // if next tile also allows hor movement, true
        if (up_platform_check(t)) {
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
    if (vertical_platform_check(t)) {
        // if next tile also allows hor movement, true
        if (down_platform_check(t)) {
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

bool Map::can_actor_move(float &x, float &y, const sf::FloatRect& collisionShape) const {
    float bot_left_x = collisionShape.left;
    float bot_right_x = collisionShape.left + collisionShape.width;

    float bot_y = collisionShape.top + collisionShape.height;

    std::vector<const Tile *> tiles_of_player = actorOnTiles(collisionShape);

    bool horizontal_mov = x != 0;
    bool up = false, right = false;

    if (horizontal_mov) {
        right = x > 0;
    }
    else {
        up = y < 0;
    }

    if (horizontal_mov && right && can_move_right(*tiles_of_player.back(), bot_right_x)) {
        y = ((tiles_of_player[0]->shape.getPosition().y + Tile::TILE_HEIGHT) - 3) - bot_y;
        return true;
    } else if (horizontal_mov && !right && can_move_left(*tiles_of_player.front(), bot_left_x)) {
        y = ((tiles_of_player[0]->shape.getPosition().y + Tile::TILE_HEIGHT) - 3) - bot_y;
        return true;
    } else {
        short up_bot_count = 0;
        bool first_time = true;
        for (const auto &tile : tiles_of_player) {
            if (!horizontal_mov && up && can_move_up(*tile, bot_y)) {
                if (first_time) {
                    x = (tile->shape.getPosition().x + Tile::TILE_WIDTH) - ((bot_right_x + bot_left_x) / 2.0);
                    first_time = false;
                }
                ++up_bot_count;
            } else if (!horizontal_mov && !up && can_move_down(*tile, bot_y)) {
                if (first_time) {
                    x = (tile->shape.getPosition().x + Tile::TILE_WIDTH) - ((bot_right_x + bot_left_x) / 2.0);
                    first_time = false;
                }
                ++up_bot_count;
            }
        }

        if (up_bot_count == 2) {
            return true;
        }
    }

    return false;
}


bool Map::can_actor_move(float &x, float &y, const Actor& actor) const {
    auto collisionShape = actor.getCollisionShape();

    return can_actor_move(x, y, collisionShape);
}

std::vector<const Tile*> Map::availableFrom(const Tile &current) const
{
    std::vector<const Tile*> availablePaths;

    if (can_move_up(current)) {
        availablePaths.push_back(&data[current.row - 1][current.col]);
    }

    if (can_move_down(current)) {
        availablePaths.push_back(&data[current.row + 1][current.col]);
    }

    if (can_move_right(current)) {
        availablePaths.push_back(&data[current.row][current.col + 1]);
    }

    if (can_move_left(current)) {
        availablePaths.push_back(&data[current.row][current.col - 1]);
    }
    
    return availablePaths;
}
