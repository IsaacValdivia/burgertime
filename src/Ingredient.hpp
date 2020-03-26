#pragma once

#include <memory>
#include <cstdint>

#include "BT_sprites.hpp"
#include "Updrawable.hpp"
#include "IngredientPiece.hpp"

class Ingredient : public Updrawable {
private:
    static const unsigned int ING_LENGTH = 4;
    bool falling;
public:
    static const char TOP_BUN = '^';
    static const char BOT_BUN = 'v';
    static const char MEAT = 'M';
    static const char CHEESE = 'C';
    static const char LETTUCE = 'L';
    static const char TOMATO = 'T';

    static const char NOT_ING = '_';

    uint8_t col;
    uint8_t row;
    char content;

    std::shared_ptr<IngredientPiece> pieces[ING_LENGTH];

    Ingredient(const float _x, const float _y, const uint8_t _col, const uint8_t _row, const char _content);

    void operator=(const Ingredient& other);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(float delta_t) override;
    
    void drop();
    void land();
};