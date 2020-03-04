#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "BurgerTimeStateMachine.hpp"

class BurgerTimeController
{
public:
    static BurgerTimeController &get();

    void run();

    ~BurgerTimeController();

private:
    BurgerTimeController();

    BurgerTimeController(const BurgerTimeController &copy);

    BurgerTimeController &operator=(const BurgerTimeController &copy);

    void startup();

    void update();

    void draw();


    std::unique_ptr<BurgerTimeStateMachine> stateMachine;

    sf::Font font;
    sf::RenderWindow window;

    std::vector<std::shared_ptr<sf::Drawable>> drawablesOnScreen;
    sf::Clock logicClock;

    friend class BurgerTimeStateMachine;
};
