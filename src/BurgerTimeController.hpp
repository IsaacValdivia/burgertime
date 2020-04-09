#pragma once

#include "GUI.hpp"

#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GUI.hpp"
#include "Config.hpp"

class BurgerTimeController {
private:
    sf::RenderWindow window; // Window

    std::list<std::weak_ptr<sf::Drawable>> drawables_on_screen; // All drawables on screen
    sf::Clock logic_clock; // Clock

    /**
     * @brief Construct a new Burger Time Controller object
     *
     */
    BurgerTimeController();

    /**
     * @brief Construct a new Burger Time Controller object
     *
     * @param copy BTC to copy from
     */
    BurgerTimeController(const BurgerTimeController &copy);

    /**
     * @brief Operator = for Burger Time Controller objects
     *
     * @param copy BTC to copy
     * @return BurgerTimeController&
     */
    BurgerTimeController &operator=(const BurgerTimeController &copy);

    /**
     * @brief Starts the Burgertime state machine, initialises audio structures
     * and restarts the timer
     *
     */
    void startup();

    /**
     * @brief Main control function
     *
     * @param delta_t delta_t
     */
    void update(float delta_t);

    /**
     * @brief Draws all drawables on screen and displays them
     *
     */
    void draw();

    /**
     * @brief Checks if the game state
     *
     * @return true
     * @return false
     */
    bool has_game_finished() const;
public:
    /**
     * @brief Singleton retriever
     *
     * @return BurgerTimeController& BTC
     */
    static BurgerTimeController &get();

    /**
     * @brief Executes Burgertime
     *
     */
    void run();

    /**
     * @brief Destroy the Burger Time Controller object
     *
     */
    ~BurgerTimeController();

    /**
     * @brief Clears all drawables on screen
     *
     */
    void clear_screen();

    /**
     * @brief Adds a new drawable object
     *
     * @param new_drawable New drawable object
     */
    void add_drawable(std::weak_ptr<sf::Drawable> new_drawable);

    /**
     * @brief Restarts the timer
     *
     */
    void restart_timer();

    /**
     * @brief Get the Elapsed Time object
     *
     * @return sf::Time Time elapsed
     */
    sf::Time get_elapsed_time();

    /**
     * @brief Sets a new resolution for the game
     *
     * @param new_resolution new resolution to set
     */
    void set_resolution(Config::Resolution new_resolution);
};