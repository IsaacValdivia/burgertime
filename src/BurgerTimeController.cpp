#include "BurgerTimeController.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <SFML/System.hpp>
#include "Constants.hpp"
#include "InputSystem.hpp"

BurgerTimeController::BurgerTimeController()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
{
    if (!font.loadFromFile(FONT_FILE))
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
    stateMachine->initialize();
}

void BurgerTimeController::run()
{
    startup();
    logicClock.restart();

    const auto logicDeltaTime = sf::seconds(LOGIC_UPDATE_FREQ);

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
    InputSystem::update();
    stateMachine->execute();
}

void BurgerTimeController::draw()
{
    window.clear();

    for (const auto &obj : drawablesOnScreen)
    {
        window.draw(*obj);
    }

    window.display();
}
