#pragma once

#include <tinyfsm.hpp>

#include <SFML/Graphics.hpp>
#include <list>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "Player.hpp"
#include "Pepper.hpp"
#include "Enemy.hpp"

class PlayingStateMachine : public tinyfsm::MooreMachine<PlayingStateMachine>
{
public:
    void react(const tinyfsm::Event &){};

    virtual void react(const ExecuteEvent &) {};

    bool hasPepper() const;

    void addPlayerAndEnemies();

    void spawnEnemy(const Enemy::Sprite_state_machine *, const Tile&, float offset);

    void ingredientCollision();

    void addPepper(const sf::Vector2f &launchPosition, Direction direction);

    void deletePepper();

protected:
    struct GameInfo
    {
        std::vector<std::shared_ptr<Map>> maps;

        std::shared_ptr<Player> player;
        std::shared_ptr<Pepper> pepper;

        std::shared_ptr<AI> ai;
        std::list<std::shared_ptr<Enemy>> enemies;

        std::shared_ptr<sf::Sprite> pepperText;

        std::array<std::shared_ptr<sf::RectangleShape>, 2> curtains;

        uint8_t currentPepper;
        uint8_t currentIngredients;
        uint8_t currentLives;
        uint32_t currentScore;
        size_t currentMap;
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

class GameOverStatePlaying : public PlayingStateMachine
{
    void entry() override;
    // void react(const ExecuteEvent &) override;
};

class GameReadyScreenState : public PlayingStateMachine
{
    void entry() override;
    void react(const ExecuteEvent &) override;
};

class NormalStatePlaying : public PlayingStateMachine
{
    void entry() override;
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
