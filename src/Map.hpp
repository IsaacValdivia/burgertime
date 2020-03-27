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

    bool horizontal_platform_check(const Tile &t) const;
    bool vertical_platform_check(const Tile &t) const;
    bool right_platform_check(const Tile &t) const;
    bool left_platform_check(const Tile &t) const;
    bool up_platform_check(const Tile &t) const;
    bool down_platform_check(const Tile &t) const;

    bool can_move_right(const Tile &t) const;
    bool can_move_left(const Tile &t) const;
    bool can_move_up(const Tile &t) const;
    bool can_move_down(const Tile &t) const;

    bool can_move_right(const Tile& t, float right_edge) const;
    bool can_move_left(const Tile& t, float left_edge) const;
    bool can_move_up(const Tile& t, float top_edge) const;
    bool can_move_down(const Tile& t, float bot_edge) const;

public:
    static constexpr int MAX_ROWS = 24;
    static constexpr int MAX_COLS = 26;

    static constexpr int Y_PADDING = 3;

    Tile data[MAX_ROWS][MAX_COLS];

    Map(const vector<string> &map_data);

    Map(const string &file_name);

    std::vector<const Tile *> actorOnTiles(const sf::FloatRect& collisionShape) const;

    std::vector<const Tile *> actorOnTiles(const Actor &actor) const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool can_actor_move(float &x, float &y, const sf::FloatRect& collisionShape) const;

    bool can_actor_move(float &x, float &y, const Actor& actor) const;

    bool outOfMap(const Actor &actor);

    std::vector<const Tile *> availableFrom(const Tile &current) const;
};
