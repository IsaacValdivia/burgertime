#pragma once

#include <string>
#include <vector>
#include <array>
#include <memory>

#include "Ingredient.hpp"
#include "Map.hpp"
#include "Tile.hpp"

/**
 * Class Map: stores a matrix of tiles, obtained from an encoded vector of strings,
 * corresponding the rows of the map to generate"
 */
class IngredientMap : public sf::Drawable {
private:
    static const char SAUSAGE = 'S';
    static const char PICKLE = 'P';
    static const char EGG = 'E';

    static const char ICE_CREAM = 'I';
    static const char COFFEE = 'C';
    static const char FRIES = 'F';

    static const char CHEF = '0';

    const unsigned int UPPER_MARGIN = 5 * Tile::TILE_HEIGHT;
    const unsigned int SIDE_MARGINS = 65;

    void fill_ingredients(const vector<string> &map_data);

    static bool isEnemy(const char c);
    static bool isItem(const char c);
    static bool isChef(const char c);

public:
    static const int MAX_ROWS = Map::MAX_ROWS;
    static const int MAX_COLS = Map::MAX_COLS;

    unsigned int num_burgers;

    std::shared_ptr<Ingredient> data[MAX_ROWS][MAX_COLS];

    std::vector<std::pair<const char, const sf::Vector2u>> enemy_spawns;
    std::pair<char, sf::Vector2u> item_spawn;
    sf::Vector2u chef_spawn;

    /**
     * Constructor, takes map coded as a vector of strings
     */
    IngredientMap(const vector<string> &map_data);

    IngredientMap(const string &file_name);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
