#pragma once

#include <tinyfsm.hpp>

#include <SFML/Graphics.hpp>
#include <list>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "Player.hpp"
#include "Pepper.hpp"
#include "Enemy.hpp"
#include "Bonus.hpp"

class PlayingStateMachine : public tinyfsm::MooreMachine<PlayingStateMachine>
{
public:
    void react(const tinyfsm::Event &){};

    virtual void react(const ExecuteEvent &) {};

    bool hasPepper() const;

    void addPlayerAndEnemies();

    void spawnEnemy(const Enemy::Type &type, const Tile&, float offset);

    void ingredientCollision();

    void addPoints(unsigned int points);

    void addPepper(const sf::Vector2f &launchPosition, Direction direction);

    void deletePepper();

    static uint32_t getCurrentScore();

protected:
    class PepperCounter
    {
        uint8_t currentPepper;

    public:
        PepperCounter();

        void changePepper(int change);
        bool hasPepper() const;
    };

    class LivesCounter
    {
        uint8_t currentLives;

    public:
        LivesCounter();

        void changeLives(int change);
        bool hasLives() const;
    };

    class ScoreCounter
    {
        uint32_t currentScore;
        uint32_t currentTopScore;

    public:
        ScoreCounter();

        void addPoints(uint32_t points);
        uint32_t getScore() const;
    };

    class LevelCounter
    {
        uint32_t currentLevel;

    public:
        LevelCounter();

        void addLevel(uint32_t level);
    };


    struct GameInfo
    {
        std::vector<std::shared_ptr<Map>> maps;

        std::shared_ptr<Player> player;
        std::shared_ptr<Pepper> pepper;

        std::shared_ptr<AI> ai;
        std::list<std::shared_ptr<Enemy>> enemies;

        std::shared_ptr<sf::Sprite> pepperText;
        std::shared_ptr<sf::Sprite> livesSprite;
        std::shared_ptr<sf::Sprite> levelSprite;

        std::shared_ptr<Bonus> bonus;

        std::array<std::shared_ptr<sf::RectangleShape>, 2> curtains;

        uint8_t currentIngredients;
        int pointsToExtraLife;
        PepperCounter pepperCounter;
        LivesCounter livesCounter;
        ScoreCounter scoreCounter;
        LevelCounter levelCounter;
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

    void checkMainMusic();

    bool mainMusicPlayed;
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
