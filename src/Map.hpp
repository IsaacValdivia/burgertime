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
    // TODO PRIVADOS Y ENUMS

    static constexpr unsigned int UPPER_MARGIN = 5 * Tile::TILE_HEIGHT;
    static constexpr unsigned int SIDE_MARGINS = 65;

    /**
     * @brief Processes a file and constructs a map from it
     *
     * @param filename
     * @return vector<string>
     */
    vector<string> process_mapfile(const string &filename) const;

    /**
     * @brief Fills the tile data structure
     *
     * @param map_data
     */
    void fill_tiles(const vector<string> &map_data);

    /**
     * @brief Fills the ingredients data structure
     *
     * @param map_data
     */
    void fill_ingredients(const vector<string> &map_data);

    /**
     * @brief Checks that the tile t allows horizontal movement
     *
     * @param t
     * @return true
     * @return false
     */
    bool horizontal_platform_check(const Tile &t) const;

    /**
     * @brief Checks that the tile t allows vertical movement
     *
     * @param t
     * @return true
     * @return false
     */
    bool vertical_platform_check(const Tile &t) const;

    /**
     * @brief Checks if the right edge of tile t has been reached
     *
     * @param t
     * @return true
     * @return false
     */
    bool right_platform_check(const Tile &t) const;

    /**
     * @brief Checks if the left edge of tile t has been reached
     *
     * @param t
     * @return true
     * @return false
     */
    bool left_platform_check(const Tile &t) const;

    /**
     * @brief Checks if the upper edge of tile t has been reached
     *
     * @param t
     * @return true
     * @return false
     */
    bool up_platform_check(const Tile &t) const;

    /**
     * @brief Checks if the lower edge of tile t has been reached
     *
     * @param t
     * @return true
     * @return false
     */
    bool down_platform_check(const Tile &t) const;

    /**
     * @brief Checks if player can move to the right on tile t
     *
     * @param t
     * @return true
     * @return false
     */
    bool can_move_right(const Tile &t) const;

    /**
     * @brief Checks if player can move to the left on tile t
     *
     * @param t
     * @return true
     * @return false
     */
    bool can_move_left(const Tile &t) const;

    /**
     * @brief Checks if player can move up on tile t
     *
     * @param t
     * @return true
     * @return false
     */
    bool can_move_up(const Tile &t) const;

    /**
     * @brief Checks if player can move down on tile t
     *
     * @param t
     * @return true
     * @return false
     */
    bool can_move_down(const Tile &t) const;

    /**
     * @brief Checks if movement to the right is possible on tile t with a certain right edge
     *
     * @param t
     * @param right_edge
     * @return true
     * @return false
     */
    bool can_move_right(const Tile &t, float right_edge) const;

    /**
     * @brief Checks if movement to the right is possible on tile t with a certain left edge
     *
     * @param t
     * @param left_edge
     * @return true
     * @return false
     */
    bool can_move_left(const Tile &t, float left_edge) const;

    /**
     * @brief Checks if movement up is possible on tile t with a certain left edge
     *
     * @param t
     * @param top_edge
     * @return true
     * @return false
     */
    bool can_move_up(const Tile &t, float top_edge) const;

    /**
     * @brief Checks if movement down is possible on tile t with a certain left edge
     *
     * @param t
     * @param bot_edge
     * @return true
     * @return false
     */
    bool can_move_down(const Tile &t, float bot_edge) const;

    /**
     * @brief Checks if c represents an enemy
     *
     * @param c
     * @return true
     * @return false
     */
    static bool isEnemy(const char c);

    /**
     * @brief Checks if c represents an item
     *
     * @param c
     * @return true
     * @return false
     */
    static bool isItem(const char c);

    /**
     * @brief Checks if c represents the chef
     *
     * @param c
     * @return true
     * @return false
     */
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

    /**
     * @brief Construct a new Map object from
     *
     * @param tile_map
     * @param ing_map
     */
    Map(const vector<string> &tile_map, const vector<string> &ing_map);

    /**
     * @brief Construct a new Map object from a string representing a path to a pair of files:
     *        a .map and a .ingmap file
     *
     * @param map_file
     */
    Map(const string &map_file);

    /**
     * @brief Return the tiles occupied by an entity
     *
     * @param entity
     * @return std::vector<std::shared_ptr<Tile>>
     */
    std::vector<std::shared_ptr<Tile>> entityOnTiles(const Entity &entity) const;

    /**
     * @brief Draws the map and ingredient map
     *
     * @param target
     * @param states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * @brief Returns if the entity can move in the direction specified by x and y,
     *        and fixes the movement to the map
     *
     * @param x
     * @param y
     * @param entity
     * @return true
     * @return false
     */
    bool can_entity_move(float &x, float &y, const Entity &entity) const;

    /**
     * @brief Checks if the actor is outside the map
     *
     * @param actor
     * @return true
     * @return false
     */
    bool outOfMap(const Actor &actor);

    /**
     * @brief Returns the tiles reachable from tile current
     *
     * @param current
     * @return std::vector<std::shared_ptr<const Tile>>
     */
    std::vector<std::shared_ptr<const Tile>> availableFrom(const Tile &current) const;

    /**
     * @brief Returns the possibles movements performable on a tile current, considering the
     *        current direction
     *
     * @param current
     * @param actual_dir
     * @return std::set<Direction>
     */
    std::set<Direction> availableFromDirection(const Tile &current, const Direction actual_dir) const;
};
