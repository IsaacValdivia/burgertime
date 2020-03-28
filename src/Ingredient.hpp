#pragma once

#include <memory>
#include <cstdint>
#include <vector>

#include "BT_sprites.hpp"
#include "Entity.hpp"
#include "SpritedEntity.hpp"

class Ingredient : public Entity {
public:
    enum Landable {
        NONE,
        INGREDIENT,
        STATIC_ING_BASKET,
        FLOOR
    };
private:
    static constexpr auto y_movement_static = 1.5;
    static constexpr auto y_movement_falling = 100;

    enum State {
        IDLE,
        FALLING,
        BOUNCE_UP_1,
        BOUNCE_UP_2,
        BOUNCE_DOWN_1,
        BOUNCE_DOWN_2,
        STATIC
    };

    static constexpr auto BOUNCE_UP_1_DURATION = 0.1;
    static constexpr auto BOUNCE_UP_2_DURATION = 0.1;
    static constexpr auto BOUNCE_DOWN_1_DURATION = 1;
    static constexpr auto BOUNCE_DOWN_2_DURATION = 0.1;

    Landable last_landable;
    State state;

    static const unsigned int ING_LENGTH = 4;

    class IngredientPiece : public SpritedEntity {
    private:
        bool stepped;

    public:

        IngredientPiece(const sf::Vector2f &_init_pos, BT_sprites::Sprite _init_sprite);

        bool isStepped() const;
        void step();

        void move_down(float delta_t);
        void move_up(float delta_t);

        friend class Ingredient;
    };

    void fix_position_down();
    void fix_position_up();
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

    void drop();

    void land(float y, Landable landable);

    bool isFalling();

    void displace_middle(const float magnitude);
    void displace_edges(const float magnitude);
};