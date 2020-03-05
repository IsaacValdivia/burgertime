#include "Tile.hpp"
#include <string>
#include <vector>

using namespace std;

class Map {
private:
    static const int MAX_TILES = 30;
    static const int MAX_ENEMY_ENTRIES = 10;
public:
    static const int TILE_HEIGHT = 4;
    static const int TILE_WIDTH  = 4;

    const unsigned int num_rows;
    const unsigned int num_cols;
    unsigned int num_burgers;

    const Tile enemy_entries[MAX_ENEMY_ENTRIES];
    const Tile chef_spawn;

    Tile data[MAX_TILES][MAX_TILES] = { {Tile()} };

    /**
     * Constructor, takes map coded as an array of chars
     */
    Map(vector<string> map_data);

};
