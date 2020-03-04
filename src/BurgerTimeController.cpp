#include "BurgerTimeController.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <SFML/System.hpp>
#include "Constants.hpp"

BurgerTimeController::BurgerTimeController()
    : window(sf::VideoMode(windowWidth, windowHeight), windowTitle)
{
    if (!font.loadFromFile(fontFile))
    {
        // TODO: error
    }
}

BurgerTimeController::~BurgerTimeController()
{
}

BurgerTimeController &BurgerTimeController::get()
{
    static BurgerTimeController instance;
    return instance;
}

void BurgerTimeController::startup()
{
    stateMachine = std::unique_ptr<BurgerTimeStateMachine>(new BurgerTimeStateMachine());
}

void BurgerTimeController::run()
{
    startup();
    logicClock.restart();

    const auto logicDeltaTime = sf::seconds(logicUpdateFreq);

    sf::Clock clock;
    auto nextTime = clock.getElapsedTime();

    while (true)
    {
        auto currentTime = clock.getElapsedTime();

        if (currentTime >= nextTime)
        {
            nextTime += logicDeltaTime;
            update();
            draw();
        }
        else
        {
            auto sleepTime = nextTime - currentTime;

            std::chrono::microseconds sleepTimeMicro(sleepTime.asMicroseconds());
            if (sleepTimeMicro.count() > 0)
            {
                std::this_thread::sleep_for(sleepTimeMicro);
            }
        }
    }
}

void BurgerTimeController::update()
{
    stateMachine->execute();
}

void BurgerTimeController::draw()
{
    window.clear();

    for (auto obj : drawablesOnScreen)
    {
        window.draw(*obj);
    }

    window.display();
}
