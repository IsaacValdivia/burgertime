#pragma once

#include "GUI.hpp"

#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GUI.hpp"
#include "Config.hpp"
#include "Stopwatch.hpp"

class BurgerTimeController {
private:
    sf::RenderWindow window; // Window
    sf::View letter_view;

    std::list<std::weak_ptr<sf::Drawable>> drawables_on_screen; // All drawables on screen
    Stopwatch logic_clock; // Clock
    Difficulty selected_difficulty;
    bool is_in_focus = true;
    unsigned int initial_map = 0;
    std::vector<sf::Vector2u> available_resolutions;

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


    /**
     * @brief from https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view
     * 
     */
    void set_letterbox_view(int windowWidth, int windowHeight);
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
     * @brief Pauses timer
     * 
     */
    void pause_timer();

    /**
     * @brief Starts timer
     * 
     */
    void start_timer();

    /**
     * @brief Returns the selected difficulty
     * 
     * @return The selected difficulty
     */
    Difficulty get_selected_difficulty() const;

    /**
     * @brief Sets a new difficulty
     * 
     * @param new_difficulty new difficulty to set
     */
    void set_difficulty(Difficulty new_difficulty);

    /**
     * @brief Sets a new resolution for the game
     *
     * @param new_resolution new resolution to set
     */
    void set_resolution(sf::Vector2u new_resolution);

    /**
     * @brief Returns the initial map
     * 
     * @return The initial map
     */
    unsigned int get_initial_map();

    /**
     * @brief Sets the initial map for the game
     *
     * @param new_initial_map new initial map to set
     */
    void set_initial_map(unsigned int new_initial_map);

    /**
     * @brief Checks if the window is in focus or not
     * 
     * @return Whether the window is on focus or not
     */
    bool is_window_on_focus() const;

    /**
     * @brief Returns the available resolutions
     * 
     * @return const std::vector<sf::Vector2u>&
     */
    const std::vector<sf::Vector2u>& get_available_resolutions() const;

    /**
     * If window mode is borderless changes it to windowed.
     * If window mode is windows changes it to borderless.
     * 
     */
    void window_borderless_switch();
};