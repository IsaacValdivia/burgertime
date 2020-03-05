#include "Map.hpp"

using namespace std;

Map::Map(vector<string> map_data) : num_cols(map_data[0].size()), num_rows(map_data.size()) {
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
};



