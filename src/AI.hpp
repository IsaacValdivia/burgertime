#pragma once

#include <memory>
#include "Map.hpp"
#include "Constants.hpp"

class AI {
private:
    std::shared_ptr<Map> map; // Pointer to map

    std::shared_ptr<const Tile> goal_tile; // Pointer to target tile

    /**
     * Returns heuristic from from tile to to tile
     *
     * @param from initial tile
     * @param to target tile
     * @return float heuristic
     */
    float h(const std::shared_ptr<const Tile> from,
            const std::shared_ptr<const Tile> to) const;

    /**
     * Returns the next direction an actor must follow to reach the player
     *
     * @param came_from
     * @param current
     * @return Direction
     */
    Direction next_move_direction(const std::map<std::shared_ptr<const Tile>,
                                  std::shared_ptr<const Tile>> came_from,
                                  const std::shared_ptr<const Tile> current) const;

public:
    static constexpr auto MAX_DISTANCE_BETWEEN_TILES = Map::MAX_ROWS + Map::MAX_COLS;

    /**
     * @brief Construct a new AI object
     *
     * @param map
     * @param new_goal_tile
     */
    AI(const std::shared_ptr<Map> map, const std::shared_ptr<const Tile> new_goal_tile);

    /**
     * @brief Get the Next Move object
     *
     * @param start_tile
     * @return Direction
     */
    Direction get_next_move(const std::shared_ptr<const Tile> start_tile) const;

    /**
     * @brief Set the Goal Tile object
     *
     * @param new_goal_tile
     */
    void set_goal_tile(const std::shared_ptr<const Tile> new_goal_tile);

    /**
     * @brief Calculates the distance to a target tile, using the heuristic (A*)
     *
     * @param from
     * @return float
     */
    float distance_to_goal(const std::shared_ptr<const Tile> from) const;
};
