#include "BurgerTimeController.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <SFML/System.hpp>
#include "Constants.hpp"
#include "InputSystem.hpp"
#include "BurgerTimeStateMachine.hpp"

BurgerTimeController::BurgerTimeController() : 
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close)
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
    BurgerTimeStateMachine::start();
    window.setKeyRepeatEnabled(false);
}

void BurgerTimeController::run()
{
    startup();
    logicClock.restart();

    const auto logicDeltaTime = sf::seconds(LOGIC_UPDATE_FREQ);

    sf::Clock clock;
    auto nextTime = clock.getElapsedTime();
    auto lastTime = clock.getElapsedTime();

    sf::Event event;

    bool isTextEntered = false;
    char charEntered;
    while (window.isOpen() && !hasGameFinished())
    {
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.setSize(sf::Vector2u(2 * WINDOW_WIDTH, 2 * WINDOW_HEIGHT));
                // window.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if ((event.text.unicode >= 'a' && event.text.unicode <= 'z') || 
                    (event.text.unicode >= 'A' && event.text.unicode <= 'Z') || 
                    (event.text.unicode >= '0' && event.text.unicode <= '9'))
                {
                    charEntered = static_cast<char>(event.text.unicode);
                    isTextEntered = true;
                }
            }
        }
        auto currentTime = clock.getElapsedTime();

        if (currentTime >= nextTime)
        {
            float deltaT = (currentTime - lastTime).asSeconds();
            nextTime += logicDeltaTime;
            if (isTextEntered)
            {
                update(deltaT, charEntered);
                isTextEntered = false;
            }
            else
            {
                update(deltaT);
            }
            draw();
            lastTime = currentTime;
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

void BurgerTimeController::update(float deltaT)
{
    InputSystem::update();
    BurgerTimeStateMachine::dispatch(ExecuteEvent(deltaT));
}

void BurgerTimeController::update(float deltaT, char charEntered)
{
    InputSystem::update(charEntered);
    BurgerTimeStateMachine::dispatch(ExecuteEvent(deltaT));
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

bool BurgerTimeController::hasGameFinished() const
{
    return BurgerTimeStateMachine::is_in_state<FinishedState>();
}
