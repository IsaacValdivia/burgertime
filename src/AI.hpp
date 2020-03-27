#pragma once

#include <memory>
#include "Map.hpp"
#include "Constants.hpp"

class AI
{
public:
    AI(const std::shared_ptr<Map> map, const Tile &newGoalTile);

    Direction getNextMove(const Tile &startTile) const;

    void setGoalTile(const Tile &newGoalTile);

private:
    float h(const Tile& from, const Tile& to) const;

    Direction nextMoveDirection(const std::map<const Tile*, const Tile*> &cameFrom, const Tile& current) const;

    std::shared_ptr<Map> map;
    
    const Tile *goalTile;
};
