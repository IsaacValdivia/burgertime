#pragma once

#include <string>
#include <vector>
#include <array>
#include <list>
#include <set>

#include "Constants.hpp"
#include "Tile.hpp"
#include "Entity.hpp"
#include "Ingredient.hpp"
#include "Actor.hpp"

using namespace std;

class Map : public sf::Drawable {
private:

    static constexpr unsigned int UPPER_MARGIN = 5 * Tile::TILE_HEIGHT;
    static constexpr unsigned int SIDE_MARGINS = 65;

    vector<string> process_mapfile(const string &filename) const;

    void fill_tiles(const vector<string> &map_data);
    void fill_ingredients(const vector<string> &map_data);

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

    bool can_move_right(const Tile &t, float right_edge) const;
    bool can_move_left(const Tile &t, float left_edge) const;
    bool can_move_up(const Tile &t, float top_edge) const;
    bool can_move_down(const Tile &t, float bot_edge) const;

    static bool isEnemy(const char c);
    static bool isItem(const char c);
    static bool isChef(const char c);

public:
    static const char ICE_CREAM = 'I';
    static const char COFFEE = 'D';
    static const char FRIES = 'F';
    static const char CHEF = '0';

    unsigned int num_burgers;
    static constexpr unsigned int MAX_ROWS = 24;
    static constexpr unsigned int MAX_COLS = 26;

    std::shared_ptr<Tile> tile_data[MAX_ROWS][MAX_COLS];
    std::vector<Ingredient> ing_data;

    std::list<std::pair<const char, const sf::Vector2u>> enemy_spawns;
    std::pair<char, sf::Vector2u> item_spawn;
    sf::Vector2u chef_spawn;

    Map(const vector<string> &tile_map, const vector<string> &ing_map);

    Map(const string &map_file);

    std::vector<std::shared_ptr<Tile>> entityOnTiles(const Entity &entity) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool can_entity_move(float &x, float &y, const Entity &entity) const;

    bool outOfMap(const Actor &actor);

    std::vector<std::shared_ptr<const Tile>> availableFrom(const Tile &current) const;

    std::set<Direction> availableFromDirection(const Tile &current, const Direction actual_dir) const;
};
