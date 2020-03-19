#pragma once

#include <tinyfsm.hpp>

#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "Player.hpp"

class PlayingStateMachine : public tinyfsm::MooreMachine<PlayingStateMachine>
{
public:
    void react(const tinyfsm::Event &){};

    virtual void react(const ExecuteEvent &){};

    void enterStateEntry();

protected:
    std::shared_ptr<Map> map;
    std::shared_ptr<Player> player;
    static BurgerTimeController &controller;
};

class EnterStatePlaying : public PlayingStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};
