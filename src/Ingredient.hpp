#include <cstdint>

class Ingredient {
private:
public:
    enum Type {
        UPPER_BREAD,
        LOWER_BREAD,
        MEAT,
        LETTUCE,
        CHEESE,
        TOMATO,
        NONE
    };

    Ingredient::Type type;
    uint8_t col;
    uint8_t row;

    Ingredient();
    Ingredient(uint8_t _col, uint8_t _row, Type _type);

    void operator=(const Ingredient& other);
};