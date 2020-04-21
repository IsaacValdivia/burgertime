#pragma once

#include "Constants.hpp"
#include "Map.hpp"

#include <memory>

class AI {
public:
    enum ExpansionMode {
        NORMAL_EXPANSION,
        OTHER_ENEMIES_EXPANSION,
    };

private:

    const std::shared_ptr<const Map> map; // Pointer to map

    std::shared_ptr<const Tile> goal_tile; // Pointer to target tile

    Direction goal_direction;

    mutable ExpansionMode expansion_mode;

    const int tiles_ahead;

    /**
     * @brief Returns heuristic from from tile to to tile
     *
     * @param from initial tile
     * @param to target tile
     * @return float heuristic
     */
    float h(const std::shared_ptr<const Tile> from,
            const std::shared_ptr<const Tile> to) const;

    /**
     * @brief Returns euclidean distance from tile from to to tile
     * 
     * @param from initial tile
     * @param to target tile
     * @return float heuristic
     */
    float h2(const std::shared_ptr<const Tile> from,
                 const std::shared_ptr<const Tile> to) const;

    /**
     * Returns the next direction an actor must follow to reach its goal
     *
     * @param came_from tiles the entity comes from
     * @param current current tiles occupied by the entity
     * @return Direction next direction the AI must take
     */
    Direction next_move_direction(const std::map<std::shared_ptr<const Tile>,
                                  std::shared_ptr<const Tile>> came_from,
                                  const std::shared_ptr<const Tile> current) const;

public:
    static constexpr auto MAX_DISTANCE_BETWEEN_TILES = Map::MAX_ROWS + Map::MAX_COLS;

    /**
     * @brief Construct a new AI object
     *
     * @param map pointer to map
     * @param new_goal_tile pointer to target tile
     */
    AI(const std::shared_ptr<const Map> map, const std::shared_ptr<const Tile> new_goal_tile, const int tiles_ahead, const ExpansionMode expansion_mode);

    /**
     * @brief Calculates the distance to a target tile, using the heuristic (A*)
     *
     * @param from source tile
     * @return float heuristic distance
     */
    float distance_to_goal(const std::shared_ptr<const Tile> from) const;

    /**
     * @brief Set the Goal Tile object
     *
     * @param new_goal_tile new target tile
     */
    void set_goal_tile(const std::shared_ptr<const Tile> new_goal_tile, Direction new_goal_direction);

    /**
     * @brief 
     * 
     * @param current 
     * @return std::vector<std::shared_ptr<const Tile>> 
     */
    std::vector<std::shared_ptr<const Tile>> expand(const Tile &current) const;

    /**
     * @brief Get the Next Move object
     *
     * @param start_tile pointer to start tile
     * @return Direction next direction to take
     */
    Direction get_next_move(const std::shared_ptr<const Tile> start_tile) const;
};
