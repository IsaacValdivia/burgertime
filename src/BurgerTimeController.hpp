#pragma once

#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GUI.hpp"

class BurgerTimeController
{
public:
    static BurgerTimeController &get();

    void run();

    ~BurgerTimeController();

    void clearScreen();

    void addDrawable(std::weak_ptr<sf::Drawable> newDrawable);

    void restartTimer();

    sf::Time getElapsedTime();


private:
    BurgerTimeController();

    BurgerTimeController(const BurgerTimeController &copy);

    BurgerTimeController &operator=(const BurgerTimeController &copy);

    void startup();

    void update(float deltaT, char charEntered);
    void update(float deltaT);

    void draw();

    bool hasGameFinished() const;

    GUI &gui;

    sf::RenderWindow window;

    std::list<std::weak_ptr<sf::Drawable>> drawablesOnScreen;
    sf::Clock logicClock;
};
