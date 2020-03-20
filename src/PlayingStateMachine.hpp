#pragma once

#include <tinyfsm.hpp>

#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "Player.hpp"
#include "Pepper.hpp"

class PlayingStateMachine : public tinyfsm::MooreMachine<PlayingStateMachine>
{
public:
    void react(const tinyfsm::Event &){};

    virtual void react(const ExecuteEvent &){};

    void addPepper(sf::Vector2f launchPosition, Direction direction);

    void deletePepper();

protected:
    std::shared_ptr<Map> map;
    std::shared_ptr<Player> player;
    std::shared_ptr<Pepper> pepper;

    std::shared_ptr<sf::Sprite> pepperText;


    uint32_t currentScore;

    static BurgerTimeController &controller;
    static GUI &gui;
};

class EnterStatePlaying : public PlayingStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};
