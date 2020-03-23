#include "IA.hpp"
#include <set>
#include <queue>
#include <map>
#include <cmath>
#include <iostream>

IA::IA(const std::shared_ptr<Map> map) : map(map)
{}

float IA::h(const Tile& from, const Tile& to) const
{
    // eclidean distance = sqrt((x1 - x2) ^ 2 + (y1 - y2) ^ 2)

    int x = to.col - from.col;
    int y = to.row - from.row;

    return sqrt(x * x + y * y);
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

    // std::cout << "previous " << (int)previous->col << " " << (int)previous->row << std::endl;


    if (previous->col > currentPtr->col)
    {
        return RIGHT;
    }
    else if (previous->col < currentPtr->col)
    {
        std::cout << "nooo" << std::endl;
        return LEFT;
    }
    else
    {
        if (previous->row > currentPtr->row)
        {
            return DOWN;
        }
        else if (previous->row < currentPtr->row)
        {
            return UP;
        }
        else
        {
            // TODO: throw exception
            return LEFT;
        }
    }
}

// https://en.wikipedia.org/wiki/A*_search_algorithm
Direction IA::getNextMove(const Tile &startTile, const Tile &goalTile) const
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
    fScore[&startTile] = h(startTile, goalTile);

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
        if (*current == goalTile)
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
                fScore[neighbor] = getGscore(neighbor) + h(*neighbor, goalTile);
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
