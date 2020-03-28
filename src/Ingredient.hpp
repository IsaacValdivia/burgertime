#pragma once

#include <memory>
#include <cstdint>
#include <vector>

#include "BT_sprites.hpp"
#include "Entity.hpp"
#include "SpritedEntity.hpp"

class Ingredient : public Entity {
private:
    class IngredientPiece : public SpritedEntity {
    private:
        static constexpr auto y_movement_static = 1.5;
        static constexpr auto y_movement_falling = 100;

    public:
        bool stepped;

        IngredientPiece(const sf::Vector2f &_init_pos, BT_sprites::Sprite _init_sprite);

        void update(float delta_t) override;

        bool isStepped() const;
        void step();
        void move();
        void drop();
        void land();

        friend class Ingredient;
    };

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

    char content;

    std::vector<IngredientPiece> pieces;

    Ingredient(const float _x, const float _y, const char _content);

    void operator=(const Ingredient &other);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(float delta_t) override;

    void stepped(const sf::FloatRect &rectangle);

    sf::FloatRect getCollisionShape() const override;

    void land(float y);

    bool isFalling();
};