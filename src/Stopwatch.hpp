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
     * TODO
     * 
     */
    Stopwatch();

    /**
     * TODO
     * 
     */
    void start();

    /**
     * TODO
     * 
     */
    void pause();

    /**
     * TODO
     * 
     */
    void restart();

    /**
     * [description]
     * 
     * @return sf::Time 
     */
    sf::Time getElapsedTime();
};
