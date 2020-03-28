#include "AI.hpp"
#include <set>
#include <queue>
#include <map>
#include <cmath>
#include <iostream>


AI::AI(const std::shared_ptr<Map> map, const std::shared_ptr<const Tile> newGoalTile) : map(map), goalTile(newGoalTile)
{}

void AI::setGoalTile(const std::shared_ptr<const Tile> newGoalTile)
{
    goalTile = newGoalTile;
}

float AI::h(const std::shared_ptr<const Tile> from, const std::shared_ptr<const Tile> to) const
{

    int x = abs(to->col - from->col);
    int y = abs(to->row - from->row);

    return (x + y);
}

Direction AI::nextMoveDirection(const std::map<std::shared_ptr<const Tile>, std::shared_ptr<const Tile>> cameFrom, const std::shared_ptr<const Tile> current) const
{
    std::shared_ptr<const Tile> previous;
    std::shared_ptr<const Tile> currentPtr = current;
    std::map<const std::shared_ptr<const Tile>, const std::shared_ptr<const Tile>>::const_iterator cameFromIt;

    while (cameFrom.find(currentPtr) != cameFrom.end())
    {
        previous = currentPtr;
        currentPtr = cameFrom.at(currentPtr);
    }

    if (!previous)
    {
        // TODO: cambiar?
        return LEFT;
    }
    
    sf::Vector2i direction(currentPtr->col - previous->col, currentPtr->row - previous->row);
    if (abs(direction.x) < abs(direction.y))
    {
        if (direction.y < 0)
        {
            return DOWN;
        }
        else
        {
            return UP;
        }
    }
    else
    {
        if (direction.x < 0)
        {
            return RIGHT;
        }
        else
        {
            return LEFT;
        }
    }
}

// https://en.wikipedia.org/wiki/A*_search_algorithm
Direction AI::getNextMove(const std::shared_ptr<const Tile> startTile) const
{
    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start
    // to n currently known.
    std::map<std::shared_ptr<const Tile>, std::shared_ptr<const Tile>> cameFrom;

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    // gScore := map with default value of Infinity
    std::map<std::shared_ptr<const Tile>, float> gScore;
    auto getGscore = [&gScore](const std::shared_ptr<const Tile> &val) {
        float scoreVal = std::numeric_limits<float>::infinity();
        if (gScore.find(val) != gScore.end())
        {
            scoreVal = gScore.at(val);
        }

        return scoreVal;
    };
    gScore[startTile] = 0;

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how short a path from start to finish can be if it goes through n.
    // fScore := map with default value of Infinity
    std::map<std::shared_ptr<const Tile>, float> fScore;
    auto getFscore = [&fScore](const std::shared_ptr<const Tile> val) {
        float scoreVal = std::numeric_limits<float>::infinity();
        if (fScore.find(val) != fScore.end())
        {
            scoreVal = fScore.at(val);
        }

        return scoreVal;
    };
    fScore[startTile] = h(startTile, goalTile);

    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather than a hash-set.
    auto comp = [&getFscore](const std::shared_ptr<const Tile> l, const std::shared_ptr<const Tile> r) {
        return getFscore(l) > getFscore(r);
    };
    std::priority_queue<std::shared_ptr<const Tile>, std::vector<std::shared_ptr<const Tile>>, decltype(comp)> openMinHeap(comp);
    std::set<std::shared_ptr<const Tile>> openSet;
    openMinHeap.push(startTile);
    openSet.emplace(startTile);


    while (!openSet.empty())
    {
        // This operation can occur in O(1) time if openMinHeap is a min-heap or a priority queue
        // current := the node in openMinHeap having the lowest fScore[] value
        const auto current = openMinHeap.top();
        if (*current == *goalTile)
        {
            return nextMoveDirection(cameFrom, current);
        }

        openMinHeap.pop();
        openSet.erase(current);
        for (const auto &neighbor : map->availableFrom(*current))
        {
            auto tentativeGscore = getGscore(current) + 1;
            if (tentativeGscore < getGscore(neighbor))
            {
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeGscore;
                fScore[neighbor] = getGscore(neighbor) + h(neighbor, goalTile);
                if (openSet.find(neighbor) == openSet.end())
                {
                    openMinHeap.push(neighbor);
                    openSet.insert(neighbor);
                }
            }
        }
    }

    // Should never happen
    // TODO: throw exception ?

    std::cerr << "THIS SHOULD NOT HAPPEN" << std::endl;

    // Open set is empty but goal was never reached
    return Direction::LEFT;
}
