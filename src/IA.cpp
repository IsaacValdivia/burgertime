#include "IA.hpp"
#include <set>
#include <queue>
#include <map>
#include <cmath>
#include <iostream>


IA::IA(const std::shared_ptr<Map> map, const Tile &newGoalTile) : map(map), goalTile(&newGoalTile)
{}

void IA::setGoalTile(const Tile &newGoalTile)
{
    goalTile = &newGoalTile;
}

float IA::h(const Tile& from, const Tile& to) const
{

    int x = abs(to.col - from.col);
    int y = abs(to.row - from.row);

    return (x + y);
}

Direction IA::nextMoveDirection(const std::map<const Tile*, const Tile*> &cameFrom, const Tile& current) const
{
    const Tile *previous;
    const Tile *currentPtr = &current;
    std::map<const Tile *, const Tile *>::const_iterator cameFromIt;

    while (cameFrom.find(currentPtr) != cameFrom.end())
    {
        previous = currentPtr;
        currentPtr = cameFrom.at(currentPtr);
    }
    std::cout << std::endl;


    sf::Vector2i direction(currentPtr->col - previous->col, currentPtr->row - previous->row);
    if (abs(direction.x) > abs(direction.y))
    {
        if (direction.x < 0)
        {
            std::cout << direction.x << " " << direction.y << std::endl;
            return RIGHT;
        }
        else
        {
            return LEFT;
        }
    }
    else
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
}

// https://en.wikipedia.org/wiki/A*_search_algorithm
Direction IA::getNextMove(const Tile &startTile) const
{
    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start
    // to n currently known.
    std::map<const Tile*, const Tile*> cameFrom;

    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    // gScore := map with default value of Infinity
    std::map<const Tile*, float> gScore;
    auto getGscore = [&gScore](const Tile *val) {
        float scoreVal = std::numeric_limits<float>::infinity();
        if (gScore.find(val) != gScore.end())
        {
            scoreVal = gScore.at(val);
        }

        return scoreVal;
    };
    gScore[&startTile] = 0;

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how short a path from start to finish can be if it goes through n.
    // fScore := map with default value of Infinity
    std::map<const Tile*, float> fScore;
    auto getFscore = [&fScore](const Tile *val) {
        float scoreVal = std::numeric_limits<float>::infinity();
        if (fScore.find(val) != fScore.end())
        {
            scoreVal = fScore.at(val);
        }

        return scoreVal;
    };
    fScore[&startTile] = h(startTile, *goalTile);

    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather than a hash-set.
    auto comp = [&getFscore](const Tile *l, const Tile *r) {
        return getFscore(l) > getFscore(r);
    };
    std::priority_queue<const Tile*, std::vector<const Tile*>, decltype(comp)> openMinHeap(comp);
    std::set<const Tile*> openSet;
    openMinHeap.push(&startTile);
    openSet.emplace(&startTile);


    while (!openSet.empty())
    {
        // This operation can occur in O(1) time if openMinHeap is a min-heap or a priority queue
        // current := the node in openMinHeap having the lowest fScore[] value
        auto current = openMinHeap.top();
        if (*current == *goalTile)
        {
            return nextMoveDirection(cameFrom, *current);
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
                fScore[neighbor] = getGscore(neighbor) + h(*neighbor, *goalTile);
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
