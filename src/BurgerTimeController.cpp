#include "BurgerTimeController.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <SFML/System.hpp>
#include "Constants.hpp"
#include "InputSystem.hpp"
#include "Audio.hpp"
#include "BurgerTimeStateMachine.hpp"

BurgerTimeController::BurgerTimeController() : 
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close), gui(GUI::get())
{
}

BurgerTimeController::~BurgerTimeController()
{
}

void BurgerTimeController::clearScreen()
{
    drawablesOnScreen.clear();
}

void BurgerTimeController::addDrawable(std::weak_ptr<sf::Drawable> newDrawable)
{
    drawablesOnScreen.push_back(newDrawable);
}

void BurgerTimeController::restartTimer()
{
    logicClock.restart();
}

sf::Time BurgerTimeController::getElapsedTime()
{
    return logicClock.getElapsedTime();
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
    Audio::init();
    restartTimer();
}

void BurgerTimeController::run()
{
    startup();

    const auto LOGIC_DELTA_TIME = sf::seconds(LOGIC_UPDATE_FREQ);

    sf::Clock clock;
    auto nextTime = clock.getElapsedTime();
    auto lastTime = clock.getElapsedTime();

    const auto MAX_TIME_DIFF = sf::seconds(0.5);
    constexpr int MAX_SKIPPED_FRAMES = 5;
    int skippedFrames = 1;

    while (window.isOpen() && !hasGameFinished())
    {
        auto currentTime = clock.getElapsedTime();

        if (currentTime - nextTime > MAX_TIME_DIFF)
        {
            nextTime = currentTime;
        }

        if (currentTime >= nextTime)
        {
            float frameTime = (currentTime - lastTime).asSeconds();
            lastTime = currentTime;
            if (frameTime > 1.3 * LOGIC_UPDATE_FREQ)
            {
                std::cerr << "Error, logica va muy lenta" << std::endl;
            }

            nextTime += LOGIC_DELTA_TIME;

            while (frameTime > 0.0)
            {
                float deltaT = std::min(frameTime, LOGIC_UPDATE_FREQ);
                update(deltaT);
                frameTime -= deltaT;
            }

            if ((currentTime < nextTime) || (skippedFrames > MAX_SKIPPED_FRAMES))
            {
                draw();
                skippedFrames = 1;
            }
            else
            {
                skippedFrames++;
            }
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
    sf::Event event;

    bool isTextEntered = false;
    char charEntered;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) 
        {
            // TODO: change
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

    if (isTextEntered)
    {
        InputSystem::update(charEntered);
        isTextEntered = false;
    }
    else
    {
        InputSystem::update();
    }
    

    BurgerTimeStateMachine::dispatch(ExecuteEvent(deltaT));
}

void BurgerTimeController::draw()
{
    window.clear();

    for (auto objWeakIt = drawablesOnScreen.begin(); objWeakIt != drawablesOnScreen.end(); ++objWeakIt)
    {
        if (auto obj = objWeakIt->lock())
        {
            window.draw(*obj);
        }
        else
        {
            drawablesOnScreen.erase(objWeakIt++);
            --objWeakIt;
        }
    }

    window.display();
}

bool BurgerTimeController::hasGameFinished() const
{
    return BurgerTimeStateMachine::is_in_state<FinishedState>();
}
