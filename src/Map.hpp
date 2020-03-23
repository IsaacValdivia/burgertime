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

    static constexpr unsigned int UPPER_MARGIN = 5 * Tile::TILE_HEIGHT;
    static constexpr unsigned int SIDE_MARGINS = 65;

    static constexpr int MAX_ROWS = 30;
    static constexpr int MAX_COLS = 26;

    std::vector<Tile> player_on_tiles(const float bot_left_x, const float bot_right_x, const float bot_y) const;

    bool can_move_right(const Tile &t) const;
    bool can_move_left(const Tile &t) const;
    bool can_move_up(const Tile &t) const;
    bool can_move_down(const Tile &t) const;

    bool can_move_right(const Tile& t, float right_edge) const;

    bool can_move_left(const Tile& t, float left_edge) const;

    bool can_move_up(const Tile& t, float top_edge) const;

    bool can_move_down(const Tile& t, float bot_edge) const;


public:


    //unsigned int num_rows;
    //unsigned int num_cols;
    //unsigned int num_burgers;

    //const Tile enemy_entries[MAX_ENEMY_ENTRIES];
    //const Tile chef_spawn;

    // TODO: cambiar a privado y hacer funciones para acceder a const Tile &
    Tile data[MAX_ROWS][MAX_COLS];

    /**
     * Constructor, takes map coded as a vector of strings
     */
    Map(const vector<string> &map_data);

    Map(const string &file_name);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool can_actor_move(float &x, float &y, const sf::Sprite& player) const;

    std::vector<const Tile*> availableFrom(const Tile &current) const;

};
