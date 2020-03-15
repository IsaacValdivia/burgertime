#pragma once

#include "Tile.hpp"
#include <string>
#include <vector>
#include <array>

using namespace std;

/**
 * Class Map: stores a matrix of tiles, obtained from an encoded vector of strings,
 * corresponding the rows of the map to generate"
 */
class Map {
private:
    void fill_tiles(const vector<string> &map_data);

    static const int MAX_ENEMY_ENTRIES = 10;
public:

    static const int MAX_ROWS = 30;
    static const int MAX_COLS = 26;

    unsigned int num_rows;
    unsigned int num_cols;
    unsigned int num_burgers;

    const Tile enemy_entries[MAX_ENEMY_ENTRIES];
    const Tile chef_spawn;

    Tile data[MAX_ROWS][MAX_COLS];

    /**
     * Constructor, takes map coded as a vector of strings
     */
    Map(const vector<string> &map_data);

    Map(const string &file_name);

};
