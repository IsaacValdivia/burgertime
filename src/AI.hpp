#pragma once

#include <memory>
#include "Map.hpp"
#include "Constants.hpp"

class AI
{
public:
    AI(const std::shared_ptr<Map> map, const std::shared_ptr<const Tile> newGoalTile);

    Direction getNextMove(const std::shared_ptr<const Tile> startTile) const;

    void setGoalTile(const std::shared_ptr<const Tile> newGoalTile);

private:
    float h(const std::shared_ptr<const Tile> from, const std::shared_ptr<const Tile> to) const;

    Direction nextMoveDirection(const std::map<std::shared_ptr<const Tile>, std::shared_ptr<const Tile>> cameFrom, const std::shared_ptr<const Tile> current) const;

    std::shared_ptr<Map> map;
    
    std::shared_ptr<const Tile> goalTile;
};
