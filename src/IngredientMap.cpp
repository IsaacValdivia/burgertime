#include "IngredientMap.hpp"
#include <fstream>
#include <iostream>
#include <typeinfo>

using namespace std;

void IngredientMap::fill_ingredients(const vector<string> &map_data) {
    unsigned int i = 0, j;
    for (auto& row : map_data) {
        j = 0;
        unsigned int ing_found = 0;
        for (auto& content : row) {
            if (content != Ingredient::NOT_ING) {
                if (ing_found <= 0) {
                    float x = SIDE_MARGINS + j * Tile::TILE_WIDTH;
                    float y = UPPER_MARGIN + i * Tile::TILE_HEIGHT;
                    data[i][j] = std::make_shared<Ingredient>(x, y, i, j, content);
                }
                ing_found = (ing_found + 1) % 4;
            }
            ++j;
        }
        ++i;
    }
}

IngredientMap::IngredientMap(const vector<string> &map_data) {
    fill_ingredients(map_data);
};

IngredientMap::IngredientMap(const string &filename) {
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
