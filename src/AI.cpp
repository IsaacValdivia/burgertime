#include "AI.hpp"
#include <set>
#include <queue>
#include <map>
#include <cmath>
#include <iostream>


AI::AI(const std::shared_ptr<Map> map,
       const std::shared_ptr<const Tile> new_goal_tile)
    : map(map), goal_tile(new_goal_tile) {}

void AI::set_goal_tile(const std::shared_ptr<const Tile> new_goal_tile) {
    goal_tile = new_goal_tile;
}

float AI::distance_to_goal(const std::shared_ptr<const Tile> from) const {
    return h(from, goal_tile);
}

float AI::h(const std::shared_ptr<const Tile> from,
            const std::shared_ptr<const Tile> to) const {

    int x = abs(to->col - from->col);
    int y = abs(to->row - from->row);

    return (x + y);
}

Direction AI::next_move_direction(const std::map<std::shared_ptr<const Tile>,
                                  std::shared_ptr<const Tile>> came_from,
                                  const std::shared_ptr<const Tile> current) const {

    std::shared_ptr<const Tile> previous;
    std::shared_ptr<const Tile> current_ptr = current;
    std::map<const std::shared_ptr<const Tile>,
        const std::shared_ptr<const Tile>>::const_iterator came_from_it;

    while (came_from.find(current_ptr) != came_from.end()) {
        previous = current_ptr;
        current_ptr = came_from.at(current_ptr);
    }

    if (!previous) {
        // TODO: cambiar?
        return LEFT;
    }

    sf::Vector2i direction(current_ptr->col - previous->col,
                           current_ptr->row - previous->row);

    if (abs(direction.x) < abs(direction.y)) {
        if (direction.y < 0) {
            return DOWN;
        }
        else {
            return UP;
        }
    }
    else {
        if (direction.x < 0) {
            return RIGHT;
        }
        else {
            return LEFT;
        }
    }
}

// https://en.wikipedia.org/wiki/A*_search_algorithm
Direction AI::get_next_move(const std::shared_ptr<const Tile> start_tile) const {
    // For node n, came_from[n] is the node immediately preceding it on the
    // cheapest path from start to n currently known.
    std::map<std::shared_ptr<const Tile>, std::shared_ptr<const Tile>> came_from;

    // For node n, g_score[n] is the cost of the cheapest path from start to n
    // currently known. g_score := map with default value of Infinity
    std::map<std::shared_ptr<const Tile>, float> g_score;
    auto get_g_score = [&g_score](const std::shared_ptr<const Tile> &val) {
        float score_val = std::numeric_limits<float>::infinity();
        if (g_score.find(val) != g_score.end()) {
            score_val = g_score.at(val);
        }

        return score_val;
    };
    g_score[start_tile] = 0;

    // For node n, f_score[n] := g_score[n] + h(n). f_score[n] represents our
    // current best guess as to how short a path from start to finish can be if
    // it goes through n. f_score := map with default value of Infinity
    std::map<std::shared_ptr<const Tile>, float> f_score;
    auto get_f_score = [&f_score](const std::shared_ptr<const Tile> val) {
        float score_val = std::numeric_limits<float>::infinity();
        if (f_score.find(val) != f_score.end()) {
            score_val = f_score.at(val);
        }

        return score_val;
    };
    f_score[start_tile] = h(start_tile, goal_tile);

    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather
    // than a hash-set.
    auto comp = [&get_f_score](const std::shared_ptr<const Tile> l,
    const std::shared_ptr<const Tile> r) {
        return get_f_score(l) > get_f_score(r);
    };
    std::priority_queue<std::shared_ptr<const Tile>,
        std::vector<std::shared_ptr<const Tile>>,
        decltype(comp)> open_min_heap(comp);

    std::set<std::shared_ptr<const Tile>> open_set;
    open_min_heap.push(start_tile);
    open_set.emplace(start_tile);

    while (!open_set.empty()) {
        // This operation can occur in O(1) time if open_min_heap is a min-heap
        // or a priority queue current := the node in open_min_heap having the
        // lowest f_score[] value
        const auto current = open_min_heap.top();
        if (*current == *goal_tile) {
            return next_move_direction(came_from, current);
        }

        open_min_heap.pop();
        open_set.erase(current);
        for (const auto &neighbor : map->available_from(*current)) {
            auto tentative_score = get_g_score(current) + 1;
            if (tentative_score < get_g_score(neighbor)) {
                // This path to neighbor is better than any previous one. Record it!
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_score;
                f_score[neighbor] = get_g_score(neighbor) + h(neighbor, goal_tile);
                if (open_set.find(neighbor) == open_set.end()) {
                    open_min_heap.push(neighbor);
                    open_set.insert(neighbor);
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
