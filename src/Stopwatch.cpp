#include "Stopwatch.hpp"

Stopwatch::Stopwatch() : is_running(false), time(sf::Time::Zero) {
    clock.restart();
}

void Stopwatch::start() {
    clock.restart();
    is_running = true;
}

void Stopwatch::pause() {
    time += clock.getElapsedTime();
    is_running = false;
}

void Stopwatch::restart() {
    time = sf::Time::Zero;
    clock.restart();
}

sf::Time Stopwatch::getElapsedTime() {
    return clock.getElapsedTime() + time;
}
