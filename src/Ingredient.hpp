#pragma once

#include "BtSprites.hpp"
#include "Entity.hpp"
#include "nod.hpp"
#include "SpritedEntity.hpp"

#include <cstdint>
#include <memory>
#include <vector>

class Ingredient : public Entity {
public:
    enum Landable {
        NONE,
        INGREDIENT,
        STATIC_ING_BASKET,
        FLOOR
    };

    enum Type : char {
        TOP_BUN = '^',
        BOT_BUN = 'v',
        MEAT = 'M',
        CHEESE = 'C',
        LETTUCE = 'L',
        TOMATO = 'T',
        NOT_ING = '_'
    };

private:
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

    static constexpr auto y_movement_static = 1.5;
    static constexpr auto bounce_movement = 3.0;
    static constexpr auto y_movement_falling = 125;

    static constexpr auto BOUNCE_DURATION = 0.10;

    static constexpr unsigned int ING_LENGTH = 4;

    const Type content;

    Landable last_landable;
    State state;

    bool static_tested;

    int num_levels;

    nod::unsafe_signal<void(float)> ingredient_moved;
    nod::unsafe_signal<void()> ingredient_stopped_moving;

    class IngredientPiece : public SpritedEntity {
    private:
        bool stepped;

    public:
        /**
         * @brief Construct a new Ingredient Piece object
         *
         * @param _init_pos initial position
         * @param _init_sprite initial sprite
         */
        IngredientPiece(const sf::Vector2f &_init_pos, const BtSprites::Sprite _init_sprite);

        /**
         * @brief Steps on the piece
         *
         */
        void step();

        /**
         * @brief Returns if the piece has been stepped
         *
         * @return true
         * @return false
         */
        bool is_stepped() const;

        /**
         * @brief Moves the piece in the y axis
         *
         * @param magnitude y offset
         */
        void move_y(const float magnitude);

        /* @brief Gets the collision shape enclosing the ingredient piece its pieces
         *
         * @return sf::FloatRect collision shape around the ingredient piece
         */
        sf::FloatRect get_collision_shape() const override;

        friend class Ingredient;
    };

    std::vector<IngredientPiece> pieces;

    /**
     * @brief Moves the ingredient down
     *
     * @param delta_t delta_t
     */
    void move_down(const float delta_t);

    /**
     * @brief Moves the item down by a fixed magnitude, independent of delta_t
     *
     * @param magnitude Y offset
     */
    void move_down_no_delta(const float magnitude);

    /**
     * @brief Fixes the position of the ingredient to the one of the lowest piece
     *
     */
    void fix_position_down();

    /**
     * @brief Fixes the position of the ingredient to the one of the highest piece
     *
     */
    void fix_position_up();

    /**
     * @brief Fixes the position to the selected y
     *
     * @param y
     */
    void fix_to_y(const float y);

    /**
     * @brief Moves the two middle pieces by a magnitude
     *
     * @param magnitude y offset
     */
    void displace_middle(const float magnitude);

    /**
     * @brief Moves the two edge pieces by a magnitude
     *
     * @param magnitude y offset
     */
    void displace_edges(const float magnitude);

    /**
     * @brief Descends a minimum of 1 level and checks where it has landed
     *
     */
    void descend_and_check();

    /**
     * @brief Reset all ingredient pieces to not stepped
     *
     */
    void reset_steps();
public:
    /**
     * @brief Construct a new Ingredient object
     *
     * @param _x X position
     * @param _y Y position
     * @param _content content
     */
    Ingredient(const float _x, const float _y, const Type _content);

    /**
     * @brief Construct a new Ingredient object
     *
     */
    Ingredient(Ingredient &&) noexcept;

    /**
     * @brief Draws all the pieces of the ingredient
     *
     * @param target target on which to draw
     * @param states drawable states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * @brief Main control function
     *
     * @param delta_t delta_t
     */
    void update(const float delta_t) override;

    /**
     * @brief Returns true if the ingredient is entirely stepped
     *
     * @param rectangle rectangle shape intersecting with ingredient
     * @param _num_levels number levels to descend
     * @return true
     * @return false
     */
    bool stepped(const sf::FloatRect &rectangle, const int _num_levels);

    /**
     * @brief Gets the collision shape enclosing the ingredient and its pieces
     *
     * @return sf::FloatRect collision shape around the entire ingredient
     */
    sf::FloatRect get_collision_shape() const override;

    /**
     * @brief Changes the ingredient state to falling
     *
     */
    void drop();

    /**
     * @brief Called when the ingredient lands on a surface
     *
     * @param y Y pos
     * @param landable landable to land on
     */
    void land(const float y, const Landable landable);

    /**
     * @brief Resets the ingredient's steps and fixes its position to the upper
     * platform
     *
     */
    void reset();

    /**
     * @brief Returns if the ingredient is basketed, can only be called once
     *
     * @return true
     * @return false
     */
    bool test_static();

    /**
     * @brief Returns if the ingredient is basketed
     *
     * @return true
     * @return false
     */
    bool is_static() const;

    /**
     * @brief Returns if the ingredient is steppable
     *
     * @return true
     * @return false
     */
    bool is_idle() const;

    /**
     * @brief Returns if the ingredient is falling
     *
     * @return true
     * @return false
     */
    bool is_falling() const;

    /**
     * @brief Returns if the ingredient is bouncing
     *
     * @return true
     * @return false
     */
    bool is_bouncing() const;

    /**
     * @brief Subscribes enemy to the surf signal
     *
     */
    std::pair<nod::connection, nod::connection> connect_enemy_surfer(
        const std::function<void(float)> &enemy_surfer_func,
        const std::function<void()> &disconnect_func);
};
