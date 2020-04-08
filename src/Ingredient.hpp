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

    bool static_tested;

    int num_levels;

    static const unsigned int ING_LENGTH = 4;

    nod::unsafe_signal<void(float)> ingredient_moved;
    nod::unsafe_signal<void()> ingredient_stopped_moving;

    class IngredientPiece : public SpritedEntity {
    private:
        bool stepped;

    public:
        /**
         * @brief Construct a new Ingredient Piece object
         *
         * @param _init_pos
         * @param _init_sprite
         */
        IngredientPiece(const sf::Vector2f &_init_pos, BtSprites::Sprite _init_sprite);

        /**
         * @brief Returns if the piece has been stepped
         *
         * @return true
         * @return false
         */
        bool is_stepped() const;

        /**
         * @brief Steps on the piece
         *
         */
        void step();

        /**
         * @brief Moves the piece in the y axis
         *
         * @param magnitude
         */
        void move_y(float magnitude);

        friend class Ingredient;
    };

    /**
     * @brief Moves the ingredient down
     *
     * @param delta_t
     */
    void move_down(const float delta_t);

    /**
     * @brief Descends a minimum of 1 level and checks where it has landed
     *
     */
    void descend_and_check();
public:
    // TODO: COSAS A PRIVADO Y ESTO A ENUM.
    static const char TOP_BUN = '^';
    static const char BOT_BUN = 'v';
    static const char MEAT = 'M';
    static const char CHEESE = 'C';
    static const char LETTUCE = 'L';
    static const char TOMATO = 'T';

    static const char NOT_ING = '_';

    char content;

    std::vector<IngredientPiece> pieces;

    /**
     * @brief Construct a new Ingredient object
     *
     * @param _x
     * @param _y
     * @param _content
     */
    Ingredient(const float _x, const float _y, const char _content);

    /**
     * @brief Construct a new Ingredient object
     *
     */
    Ingredient(Ingredient &&) noexcept;

    /**
     * @brief = operator for ingredients
     *
     * @param other
     */
    void operator=(const Ingredient &other);

    /**
     * @brief Draws all the pieces of the ingredient
     *
     * @param target
     * @param states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * @brief Main control function
     *
     * @param delta_t
     */
    void update(float delta_t) override;

    /**
     * @brief Returns
     *
     * @param rectangle
     * @param _num_levels
     * @return true
     * @return false
     */
    bool stepped(const sf::FloatRect &rectangle, const int _num_levels);

    /**
     * @brief Gets the collision shape enclosing the ingredient and its pieces
     *
     * @return sf::FloatRect
     */
    sf::FloatRect get_collision_shape() const override;

    /**
     * @brief Changes the ingredient state to falling
     *
     */
    void drop();

    /**
     * @brief Moves the item down by a fixed magnitude, independent of delta_t
     *
     * @param magnitude
     */
    void move_down_no_delta(const float magnitude);

    /**
     * @brief Called when the ingredient lands on a surface
     *
     * @param y
     * @param landable
     */
    void land(const float y, const Landable landable);

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
     * @brief Reset all ingredient pieces to not stepped
     *
     */
    void reset_steps();

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
     * @param magnitude
     */
    void displace_middle(const float magnitude);

    /**
     * @brief Moves the two edge pieces by a magnitude
     *
     * @param magnitude
     */
    void displace_edges(const float magnitude);

    /**
     * @brief Subscribes enemy to the surf signal
     *
     */
    std::pair<nod::connection, nod::connection> connect_enemy_surfer(
        const std::function<void(float)> &enemy_surfer_func,
        const std::function<void()> &disconnect_func);
};
