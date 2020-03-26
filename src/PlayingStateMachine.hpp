#pragma once

#include <tinyfsm.hpp>

#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "Player.hpp"
#include "Pepper.hpp"
#include "Enemy.hpp"
#include "IngredientMap.hpp"

class PlayingStateMachine : public tinyfsm::MooreMachine<PlayingStateMachine>
{
public:
    void react(const tinyfsm::Event &){};

    virtual void react(const ExecuteEvent &){};

    void addPepper(const sf::Vector2f &launchPosition, Direction direction);

    void deletePepper();

protected:
    struct GameInfo
    {
        std::shared_ptr<Map> map;
        std::shared_ptr<IngredientMap> ingmap;
        std::shared_ptr<Player> player;
        std::shared_ptr<Pepper> pepper;

        std::vector<std::shared_ptr<Enemy>> enemies;

        std::vector<IA> ias;

        std::shared_ptr<sf::Sprite> pepperText;

        std::array<std::shared_ptr<sf::RectangleShape>, 2> curtains;

        uint32_t currentScore;
    };

    void changeGameInfo();

    void setGameInfo(std::unique_ptr<GameInfo> newGameInfo);

    std::unique_ptr<GameInfo> gameInfo;

    static BurgerTimeController &controller;
    static GUI &gui;
};

class EnterStatePlaying : public PlayingStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class NormalStatePlaying : public PlayingStateMachine
{
    // void entry() override;
    void react(const ExecuteEvent &) override;
};

class WinStatePlaying : public PlayingStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class DeadStatePlaying : public PlayingStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};
