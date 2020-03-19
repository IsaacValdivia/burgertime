#pragma once

#include "Tile.hpp"
#include "Actor.hpp"
#include <string>
#include <vector>
#include <array>

using namespace std;

/**
 * Class Map: stores a matrix of tiles, obtained from an encoded vector of strings,
 * corresponding the rows of the map to generate"
 */
class Map : public sf::Drawable {
private:
    void fill_tiles(const vector<string> &map_data);

    static const int MAX_ENEMY_ENTRIES = 10;

    static constexpr float TILE_WIDTH = 16.0;
    static constexpr float TILE_HEIGHT = 16.0;
    static constexpr float HOR_COLL_LOOKAHEAD_CORR = 5; //Actor::x_walking_speed; // TO_DO: AJUSTAR
    static constexpr float VERT_COLL_LOOKAHEAD_CORR = 5; //Actor::y_walking_speed;

    const unsigned int UPPER_MARGIN = 5 * TILE_HEIGHT;
    const unsigned int SIDE_MARGINS = 65;

    std::vector<Tile> player_on_tiles(const float left_edge, const float right_edge, const float upper_edge, const float lower_edge) const;

    bool can_move_right(const Tile& t, float right_edge) const;

public:

    static const int MAX_ROWS = 30;
    static const int MAX_COLS = 26;

    //unsigned int num_rows;
    //unsigned int num_cols;
    //unsigned int num_burgers;

    //const Tile enemy_entries[MAX_ENEMY_ENTRIES];
    //const Tile chef_spawn;

    Tile data[MAX_ROWS][MAX_COLS];

    /**
     * Constructor, takes map coded as a vector of strings
     */
    Map(const vector<string> &map_data);

    Map(const string &file_name);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool player_can_move(float &x, float &y, const sf::Sprite& player) const;

};
