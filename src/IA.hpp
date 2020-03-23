#pragma once

#include <memory>
#include "Map.hpp"
#include "Constants.hpp"

class IA
{
public:
    IA(const std::shared_ptr<Map> map);


    Direction getNextMove(const Tile &currenTile, const Tile &goalTile);

private:
    int h(sf::Vector2u from, sf::Vector2u to);

    std::shared_ptr<Map> map;
};