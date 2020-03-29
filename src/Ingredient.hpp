#pragma once

#include <memory>
#include <cstdint>
#include <vector>
#include "nod.hpp"

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
    static constexpr auto bounce_movement = 4.0;
    static constexpr auto y_movement_falling = 125;

    enum State {
        IDLE,
        FALLING,
        BOUNCE_UP_1,
        BOUNCE_UP_2,
        BOUNCE_UP_3,
        BOUNCE_DOWN_1,
        BOUNCE_DOWN_2,
        BOUNCE_DOWN_3,
        STATIC
    };

    static constexpr auto BOUNCE_DURATION = 0.10;

    Landable last_landable;
    State state;

    bool staticTested;

    int num_levels;

    static const unsigned int ING_LENGTH = 4;

    nod::unsafe_signal<void(float)> ingredient_moved;
    nod::unsafe_signal<void()> ingredient_stopped_moving;

    class IngredientPiece : public SpritedEntity {
    private:
        bool stepped;

    public:

        IngredientPiece(const sf::Vector2f &_init_pos, BT_sprites::Sprite _init_sprite);

        bool isStepped() const;
        void step();

        void move_y(float magnitude);

        friend class Ingredient;
    };

    void move_down(const float delta_t);
    void descend_and_check();
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

    Ingredient(Ingredient &&) noexcept;

    void operator=(const Ingredient &other);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(float delta_t) override;

    bool stepped(const sf::FloatRect &rectangle, const int _num_levels);

    sf::FloatRect getCollisionShape() const override;

    void drop();

    void move_down_no_delta(const float magnitude);

    void land(float y, Landable landable);

    bool testStatic();

    bool isStatic() const;

    bool isIdle() const;

    bool isFalling() const;

    bool isBouncing() const;

    void resetSteps();
    void fix_position_down();
    void fix_position_up();

    void fix_to_y(const float y);

    void displace_middle(const float magnitude);
    void displace_edges(const float magnitude);

    std::pair<nod::connection, nod::connection> connect_enemy_surfer(const std::function<void(float)> &enemy_surfer_func, const std::function<void()> &disconnect_func);
};
