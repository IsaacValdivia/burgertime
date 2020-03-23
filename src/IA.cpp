#include "IA.hpp"
#include <set>
#include <queue>
#include <map>

IA::IA(const std::shared_ptr<Map> map) : map(map)
{}

int h(sf::Vector2u from, sf::Vector2u to)
{
    // todo:
}


Direction IA::getNextMove(const Tile &currentTile, const Tile &goalTile)
{
    sf::Vector2u startPos = sf::Vector2u(currentTile.col, currentTile.row);
    sf::Vector2u goalPos = sf::Vector2u(goalTile.col, goalTile.row);

    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start
    // to n currently known.
    std::map<sf::Vector2u, sf::Vector2u> cameFrom;


    // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
    // gScore := map with default value of Infinity
    std::map<sf::Vector2u, int> gScore;
    gScore[startPos] = 0;

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how short a path from start to finish can be if it goes through n.
    // fScore := map with default value of Infinity
    std::map<sf::Vector2u, int> fScore;
    fScore[startPos] = h(startPos, goalPos);

    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather than a hash-set.
    auto comp = [&fScore](const sf::Vector2u &l, const sf::Vector2u &r) {
        return fScore[l] < fScore[r];
    };
    std::priority_queue<sf::Vector2u, std::vector<sf::Vector2u>, decltype(comp)> openMinHeap(comp);
    std::set<sf::Vector2u> openSet;
    openMinHeap.push(startPos);
    openSet.insert(startPos);


    while (!openSet.empty())
    {
        // This operation can occur in O(1) time if openMinHeap is a min-heap or a priority queue
        // current := the node in openMinHeap having the lowest fScore[] value
        auto current = openMinHeap.top();
        if (current == goalPos)
        {
            return reconstruct_path(cameFrom, current)
        }

        openMinHeap.pop();
        openSet.erase(current);
        for (const auto &neighbor : map->availableFrom(current))
        {
            auto tentativeGscore = gScore[current] + 1;
            if (tentativeGscore < gScore[neighbor])
            {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeGscore;
                fScore[neighbor] = gScore[neighbor] + h(neighbor, goalPos);
                if (openSet.find(neighbor) == openSet.end())
                {
                    openSet.insert(neighbor);
                }
            }
        }

        for each neighbor of current
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            tentative_gScore := gScore[current] + d(current, neighbor)
            if tentative_gScore < gScore[neighbor]
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighbor] := current
                gScore[neighbor] := tentative_gScore
                fScore[neighbor] := gScore[neighbor] + h(neighbor)
                if neighbor not in openSet
                    openSet.add(neighbor)
    }


    // Open set is empty but goal was never reached
    return failure
}
