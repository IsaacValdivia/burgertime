#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Stopwatch {
private:
    sf::Clock clock;

    sf::Time time;

    bool is_running;

public:
    /**
     * @brief Construct a new Stopwatch object
     * 
     */
    Stopwatch();

    /**
     * Start/resume the stopwatch
     * 
     */
    void start();

    /**
     * Pause the stopwatch
     * 
     */
    void pause();

    /**
     * Restart the stopwatch
     * 
     */
    void restart();

    /**
     * Get elapsed time.
     * 
     * @return sf::Time 
     */
    sf::Time getElapsedTime();
};
