#include "Map.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void Map::fill_tiles(const vector<string> &map_data) {
    unsigned int i = -1, j;
    for (auto& row : map_data) {
        ++i;
        j = 0;
        for (auto& c : row) {
        	Tile t(i, j, c);
            data[i][j] = t;
            ++j;
        }
    }
}

Map::Map(const vector<string> &map_data) : num_cols(map_data[0].size()), num_rows(map_data.size()) {
    fill_tiles(map_data);
};

Map::Map(const string &filename) {
    ifstream f;
    f.open(filename);

    if (f.is_open()) {
        vector<string> rows;
        char row_aux[18];
        string row;
        while (!f.eof()) {
            f.getline(row_aux, 18);
            row = row_aux;
            int s = row.size();
            if (s != 17) {
                throw runtime_error("Rows can only have 17 tiles");
            }
            rows.push_back(row);
        }
        
        fill_tiles(rows);
        f.close();
    } else {
        throw runtime_error("File " + filename + " could not be found");
    }
}

