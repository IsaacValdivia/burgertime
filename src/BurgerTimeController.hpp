#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

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

    bool hasGameFinished() const;

    sf::Font font;
    sf::RenderWindow window;

    std::vector<std::shared_ptr<sf::Drawable>> drawablesOnScreen;
    sf::Clock logicClock;

    friend class BurgerTimeStateMachine;
    friend class MainScreenStateMachine;
    friend class GameOverScreenState;
};
