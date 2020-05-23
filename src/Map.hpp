#pragma once

#include "Actor.hpp"
#include "Constants.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "Ingredient.hpp"
#include "Tile.hpp"

#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <list>
#include <set>

class Map : public sf::Drawable {
public:
    static constexpr unsigned int MAX_ROWS = 24;
    static constexpr unsigned int MAX_COLS = 26;

    enum SpecialItem : char {
        ICE_CREAM = 'I',
        COFFEE = 'D',
        FRIES = 'F',
    };

private:
    static constexpr unsigned int UPPER_MARGIN = 5 * Tile::TILE_HEIGHT;
    static constexpr unsigned int SIDE_MARGINS = 65;

    unsigned int num_burgers;

    std::shared_ptr<Tile> tile_data[MAX_ROWS][MAX_COLS];
    std::vector<Ingredient> ing_data;

    std::list<std::pair<Enemy::Type, const sf::Vector2u>> enemy_spawns;
    std::pair<SpecialItem, sf::Vector2u> item_spawn;
    sf::Vector2u chef_spawn;

    mutable std::map<std::shared_ptr<const Tile>, std::set<Enemy*>> old_enemies_positions;
    mutable std::map<std::shared_ptr<const Tile>, std::set<Enemy*>> enemies_positions;

    /**
     * @brief Processes a file and constructs a map from it
     *
     * @param filename path to file to load
     * @return vector<string> data of map
     */
    std::vector<std::string> process_mapfile(const std::string &filename) const;

    /**
     * @brief Fills the tile data structure
     *
     * @param map_data tile map data
     */
    void fill_tiles(const std::vector<std::string> &map_data);

    /**
     * @brief Fills the ingredients data structure
     *
     * @param map_data ingredient map data
     */
    void fill_ingredients(const std::vector<std::string> &map_data);

    /**
     * @brief Checks that the tile t allows horizontal movement
     *
     * @param t tile
     * @return true
     * @return false
     */
    bool horizontal_platform_check(const Tile &t) const;

    /**
     * @brief Checks that the tile t allows vertical movement
     *
     * @param t tile to check
     * @return true
     * @return false
     */
    bool vertical_platform_check(const Tile &t) const;

    /**
     * @brief Checks if the right edge of tile t has been reached
     *
     * @param t tile to check
     * @return true
     * @return false
     */
    bool right_platform_check(const Tile &t) const;

    /**
     * @brief Checks if the left edge of tile t has been reached
     *
     * @param t tile to check
     * @return true
     * @return false
     */
    bool left_platform_check(const Tile &t) const;

    /**
     * @brief Checks if the upper edge of tile t has been reached
     *
     * @param t tile to check
     * @return true
     * @return false
     */
    bool up_platform_check(const Tile &t) const;

    /**
     * @brief Checks if the lower edge of tile t has been reached
     *
     * @param t tile to check
     * @return true
     * @return false
     */
    bool down_platform_check(const Tile &t) const;

    /**
     * @brief Checks if player can move to the right on tile t
     *
     * @param t tile to check
     * @return true
     * @return false
     */
    bool can_move_right(const Tile &t) const;

    /**
     * @brief Checks if player can move to the left on tile t
     *
     * @param t tile to check
     * @return true
     * @return false
     */
    bool can_move_left(const Tile &t) const;

    /**
     * @brief Checks if player can move up on tile t
     *
     * @param t tile to check
     * @return true
     * @return false
     */
    bool can_move_up(const Tile &t) const;

    /**
     * @brief Checks if player can move down on tile t
     *
     * @param t tile to check
     * @return true
     * @return false
     */
    bool can_move_down(const Tile &t) const;

    /**
     * @brief Checks if movement to the right is possible on tile t with a certain right edge
     *
     * @param t tile to check
     * @param right_edge right edge
     * @return true
     * @return false
     */
    bool can_move_right(const Tile &t, const float right_edge) const;

    /**
     * @brief Checks if movement to the right is possible on tile t with a certain left edge
     *
     * @param t tile to check
     * @param left_edge left edge
     * @return true
     * @return false
     */
    bool can_move_left(const Tile &t, const float left_edge) const;

    /**
     * @brief Checks if movement to the right is possible on tile above t with a certain right edge
     *
     * @param t tile to check
     * @param right_edge right edge
     * @return true
     * @return false
     */
    bool can_move_right_upper(const Tile &t, const float right_edge) const;

    /**
     * @brief Checks if movement to the right is possible on tile above t with a certain left edge
     *
     * @param t tile to check
     * @param left_edge left edge
     * @return true
     * @return false
     */
    bool can_move_left_upper(const Tile &t, const float left_edge) const;

    /**
     * @brief Checks if movement up is possible on tile t with a certain left edge
     *
     * @param t tile to check
     * @param top_edge top edge
     * @return true
     * @return false
     */
    bool can_move_up(const Tile &t, const float top_edge) const;

    /**
     * @brief Checks if movement down is possible on tile t with a certain left edge
     *
     * @param t tile to check
     * @param bot_edge bottom edge
     * @return true
     * @return false
     */
    bool can_move_down(const Tile &t, const float bot_edge) const;

    /**
     * @brief Checks if c represents an enemy
     *
     * @param c character representation
     * @return true
     * @return false
     */
    static bool is_enemy(const char c);

    /**
     * @brief Checks if c represents an item
     *
     * @param c character representation
     * @return true
     * @return false
     */
    static bool is_item(const char c);

    /**
     * @brief Checks if c represents the chef
     *
     * @param c character representation
     * @return true
     * @return false
     */
    static bool is_chef(const char c);

    /**
     * @brief Returns the possibles movements performable on a tile current, considering the
     *        current direction
     *
     * @param current current tile
     * @param available_paths 
     * @param tiles_ahead tile offset to check the movement t
     */
    void available_from_direction_inm(const std::shared_ptr<const Tile> &current, 
                        std::vector<std::shared_ptr<const Tile>> &available_paths, int tiles_ahead,
                        const Direction actual_dir) const;

public:
    enum Chef : char {
        CHEF = '0'
    };

    /**
     * @brief Construct a new Map object from a string representing a path to a
     * pair of files: a .map and a .ingmap file
     *
     * @param map_file maps path + name
     */
    Map(const std::string &map_file);

    /**
     * @brief Draws the map and ingredient map
     *
     * @param target target to draw on
     * @param states states of drawable
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * @brief Return the tiles occupied by an entity
     *
     * @param entity entity to check tiles
     * @return std::vector<std::shared_ptr<Tile>>
     */
    std::vector<std::shared_ptr<Tile>> entity_on_tiles(const Entity &entity) const;

    /**
     * @brief Returns if the entity can move in the direction specified by x and y,
     *        and fixes the movement to the map
     *
     * @param x x offset to move in
     * @param y y offset to move in
     * @param entity entity that wants to move
     * @return true
     * @return false
     */
    bool can_entity_move(float &x, float &y, const Entity &entity) const;

    /**
     * @brief Checks if the actor is outside the map
     *
     * @param actor actor to check
     * @return true
     * @return false
     */
    bool out_of_map(const Actor &actor) const;

    /**
     * @brief Returns the enemies that are on the given tile a frame ago
     *
     * @param tile tile to check against
     * @return std::set<std::shared_ptr<Enemy>>
     */
    std::set<Enemy *> enemies_on_tile(const std::shared_ptr<const Tile> &tile) const;

    /**
     * @brief Returns the enemies that are on the given tile
     *
     * @param tile tile to check against
     * @return std::set<std::shared_ptr<Enemy>>
     */
    std::set<Enemy *> enemies_on_tiles_now(const std::shared_ptr<const Tile> &tile) const;

    /**
     * @brief Resets the enemies on tiles
     *
     */
    void reset_enemies_on_tiles();

    /**
     * @brief Set the enemy on tile
     * 
     * @param enemy enemy to place
     * @param tile tile to place on
     */
    void set_enemy_on_tile(Enemy *enemy, std::shared_ptr<const Tile> tile);

    /**
     * @brief Returns the tiles reachable from tile current
     *
     * @param current tile
     * @return std::vector<std::shared_ptr<const Tile>>
     */
    std::vector<std::shared_ptr<const Tile>> available_from(const Tile &current) const;

    /**
     * @brief Returns the possibles movements performable on a tile current, considering the
     *        current direction
     *
     * @param current current tile
     * @param actual_dir current direction
     * @return std::set<Direction>
     */
    std::set<Direction> available_from_direction(const Tile &current,
            const Direction actual_dir) const;

    /**
     * @brief Returns the possibles movements performable on a tile current, considering the
     *        current direction
     *
     * @param current current tile
     * @param actual_dir current direction
     * @param tiles_ahead tile offset to check the movement t
     * @return std::set<Direction>
     */
    std::vector<std::shared_ptr<const Tile>> available_from_direction(const std::shared_ptr<const Tile> &current,
            const Direction actual_dir, const int tiles_ahead) const;

    /**
     * @brief Returns the starting tile of the chef
     *
     * @return std::shared_ptr<const Tile> ptr to tile
     */
    std::shared_ptr<const Tile> get_chef_initial_tile() const;

    /**
     * @brief Returns the starting tile of the special item
     *
     * @return std::shared_ptr<const Tile> ptr to tile
     */
    std::shared_ptr<const Tile> get_item_initial_tile() const;

    /**
     * @brief Get the type of the special item
     *
     * @return SpecialItem
     */
    SpecialItem get_item_type() const;

    /**
     * @brief Returns the starting tiles of the enemies
     *
     * @return std::vector<std::pair<Enemy::Type, std::shared_ptr<const Tile>>> vector of ptrs to tiles
     */
    std::vector<std::pair<Enemy::Type, std::shared_ptr<const Tile>>>
    get_enemies_spawns() const;

    /**
     * @brief Return data of all ingredients
     *
     * @return const std::vector<Ingredient>& vector of ingredients
     */
    std::vector<Ingredient> &get_ing_data();
};
