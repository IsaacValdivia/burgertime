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
                    enemy_spawns.push_back(std::make_pair(content, sf::Vector2u(i,j)));
                } else if (isItem(content)) {
                    item_spawn.first = content;
                    item_spawn.second = sf::Vector2u(i,j);
                } else if (isChef(content)) {
                    chef_spawn = sf::Vector2u(i,j);
                } else {
                    if (ing_found <= 0) {
                        if (content == Ingredient::TOP_BUN) {
                            ++num_burgers;
                        }
                        float x = SIDE_MARGINS + j * Tile::TILE_WIDTH;
                        float y = UPPER_MARGIN + i * Tile::TILE_HEIGHT;
                        data[i][j] = std::make_shared<Ingredient>(x, y, i, j, content);
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
    for (auto &row : data) {
        for (auto &ing : row) {
            if (ing) {
                target.draw(*ing, states);
            }
        }
    }
}
