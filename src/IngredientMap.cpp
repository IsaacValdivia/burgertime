#include "IngredientMap.hpp"
#include <fstream>
#include <iostream>
#include <typeinfo>

using namespace std;

bool IngredientMap::isEnemy(const char c) {
    return c == SAUSAGE || c == EGG || c == PICKLE;
}

bool IngredientMap::isItem(const char c) {
    return c == ICE_CREAM || c == COFFEE || c == FRIES;
}

bool IngredientMap::isChef(const char c) {
    return c == CHEF;
}

void IngredientMap::fill_ingredients(const vector<string> &map_data) {
    unsigned int i = 0, j;
    for (auto& row : map_data) {
        j = 0;
        unsigned int ing_found = 0;
        for (auto& content : row) {
            if (content != Ingredient::NOT_ING) {
                if (isEnemy(content)) {
                    enemy_spawns.push_front(std::make_pair(content, sf::Vector2u(i,j)));
                } else if (isItem(content)) {
                    item_spawn.first = content;
                    item_spawn.second = sf::Vector2u(i,j);
                } else if (isChef(content)) {
                    chef_spawn = sf::Vector2u(i,j);
                } else {
                    //ingredient_mask[i][j] = true;
                    if (ing_found <= 0) {
                        if (content == Ingredient::TOP_BUN) {
                            ++num_burgers;
                        }
                        float x = SIDE_MARGINS + j * Tile::TILE_WIDTH;
                        float y = UPPER_MARGIN + i * Tile::TILE_HEIGHT;
                        data.push_back(Ingredient(x, y, i, j, content));
                        //data[i][j] = std::make_shared<Ingredient>(x, y, i, j, content);
                    }
                    ing_found = (ing_found + 1) % 4;
                }
            }
            ++j;
        }
        ++i;
    }
}

IngredientMap::IngredientMap(const vector<string> &map_data) : num_burgers(0) {
    fill_ingredients(map_data);
};

IngredientMap::IngredientMap(const string &filename) : num_burgers(0) {
    ifstream f;
    f.open(filename);

    if (f.is_open()) {
        vector<string> rows;
        char row_aux[MAX_COLS + 1];
        string row;
        while (!f.eof()) {
            f.getline(row_aux, MAX_COLS + 1);
            row = row_aux;
            int s = row.size();
            if (s != MAX_COLS) {
                throw runtime_error("Rows can only have " + to_string(MAX_COLS) + " tiles");
            }
            rows.push_back(row);
        }
        
        f.close();
        fill_ingredients(rows);
    } else {
        throw runtime_error("File " + filename + " could not be found");
    }
}

void IngredientMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto &ing : data) {
        target.draw(ing, states);
    }
}

// sf::Vector2u IngredientMap::retrieve_coords(const sf::Vector2f &position) const {
//     return sf::Vector2u((position.x - (SIDE_MARGINS + 1)) / Tile::TILE_WIDTH, (position.y - (UPPER_MARGIN + 1)) / Tile::TILE_HEIGHT);
// }

// std::shared_ptr<Ingredient> IngredientMap::retrieve_ing(const unsigned int x, const unsigned int y) const {
//     if (data[x][y]) {
//         return data[x][y];
//     }
//     else if (data[x-1][y]) {
//         return data[x-1][y];
//     }
//     else if (data[x-2][y]) {
//         return data[x-2][y];
//     }
//     else {
//         return data[x-3][y];
//     }
// }

// void IngredientMap::check_step(const sf::Vector2f &position) {
//     // A partir de x e y, ver si hay que actualizar ingrediente
//     const sf::Vector2u step_coords = retrieve_coords(position);
//     // Si si, actualizar ingrediente
//     if (ingredient_mask[step_coords.x][step_coords.y]) {
//         std::shared_ptr<Ingredient> ing = retrieve_ing(step_coords.x, step_coords.y);
//         //ing->update();
//     }
// }