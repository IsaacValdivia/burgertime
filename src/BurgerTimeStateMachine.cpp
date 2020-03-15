#include "BurgerTimeStateMachine.hpp"

#include <memory>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include "InputSystem.hpp"
#include "MainScreenStateMachine.hpp"
#include "PlayingStateMachine.hpp"
#include "BT_sprites.hpp"
#include "HighScores.hpp"


FSM_INITIAL_STATE(BurgerTimeStateMachine, HighscoreDisplayScreenState)

BurgerTimeController &BurgerTimeStateMachine::controller = BurgerTimeController::get();


bool BurgerTimeStateMachine::timedStateReact()
{
    if (hasInputJustBeenPressed(InputSystem::Input::PAUSE))
    {
       controller.logicClock.restart();
       return true;
    }

    auto elapsedTime = controller.logicClock.getElapsedTime();
    if (elapsedTime.asSeconds() >= getWaitTime())
    {
        controller.logicClock.restart();
        return true;
    }

    return false;
}


void BurgerTimeStateMachine::highscoreDisplayScreenStateEntry()
{
    controller.drawablesOnScreen.clear();

    auto burgerTimeText = std::make_shared<sf::Text>();
    burgerTimeText->setFillColor(sf::Color::Red);
    burgerTimeText->setScale(0.70, 0.70);
    burgerTimeText->setFont(controller.font);
    burgerTimeText->setString("BURGER TIME");
    burgerTimeText->setPosition(28 * WINDOW_WIDTH / 100, 15 * WINDOW_HEIGHT / 100);

    auto bestFivePlayersText = std::make_shared<sf::Text>();
    bestFivePlayersText->setFillColor(sf::Color::White);
    bestFivePlayersText->setScale(0.70, 0.70);
    bestFivePlayersText->setFont(controller.font);
    bestFivePlayersText->setString("BEST FIVE PLAYERS");
    bestFivePlayersText->setPosition(18 * WINDOW_WIDTH / 100, 30 * WINDOW_HEIGHT / 100);

    HighScores highScores("welp.hscores");
    auto hScores = highScores.getHighScores();

    for (int i = 0; i < HighScores::NUM_HIGH_SCORES; ++i)
    {
        auto scoreStr = std::to_string(hScores[i].second);
        std::string whiteSpace(" ");

        for (uint8_t j = 0; j < HighScores::MAX_SCORE_CHARS - scoreStr.length(); ++j)
        {
            whiteSpace += " ";
        }

        std::shared_ptr<sf::Text> hScoreText = std::make_shared<sf::Text>();
        hScoreText->setFillColor(sf::Color::White);
        hScoreText->setScale(0.70, 0.70);
        hScoreText->setFont(controller.font);
        hScoreText->setString(std::to_string(i + 1) + " " + hScores[i].first.data() + whiteSpace + scoreStr + " PTS");
        hScoreText->setPosition(18 * WINDOW_WIDTH / 100, (45 + i * 10) * WINDOW_HEIGHT / 100);
        controller.drawablesOnScreen.push_back(hScoreText);
    }

    controller.drawablesOnScreen.push_back(burgerTimeText);
    controller.drawablesOnScreen.push_back(bestFivePlayersText);
    controller.logicClock.restart();
}

void HighscoreDisplayScreenState::entry()
{
    BurgerTimeStateMachine::highscoreDisplayScreenStateEntry();
}

void HighscoreDisplayScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact())
    {
        transit<ItemPointsScreenState>();
    }
}


void BurgerTimeStateMachine::itemPointsScreenStateEntry()
{
    // TODO: change magic numbers to constants and mb reduce code size

    controller.drawablesOnScreen.clear();

    auto burgerTimeText = std::make_shared<sf::Text>();
    burgerTimeText->setFillColor(sf::Color::Red);
    burgerTimeText->setScale(0.70, 0.70);
    burgerTimeText->setFont(controller.font);
    burgerTimeText->setString("BURGER TIME");
    burgerTimeText->setPosition(28 * WINDOW_WIDTH / 100, 15 * WINDOW_HEIGHT / 100);

    auto scoreText = std::make_shared<sf::Text>();
    scoreText->setFillColor(sf::Color::White);
    scoreText->setScale(0.70, 0.70);
    scoreText->setFont(controller.font);
    scoreText->setString("-SCORE-");
    scoreText->setPosition(34 * WINDOW_WIDTH / 100, 23 * WINDOW_HEIGHT / 100);


    auto topBun1 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*topBun1, BT_sprites::Sprite::TOP_BREAD_1);
    topBun1->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    topBun1->setScale(2, 2);

    auto topBun2 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*topBun2, BT_sprites::Sprite::TOP_BREAD_2);
    topBun2->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    topBun2->move(16, 0);
    topBun2->setScale(2, 2);

    auto topBun3 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*topBun3, BT_sprites::Sprite::TOP_BREAD_3);
    topBun3->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    topBun3->move(2 * 16, 0);
    topBun3->setScale(2, 2);

    auto topBun4 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*topBun4, BT_sprites::Sprite::TOP_BREAD_4);
    topBun4->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    topBun4->move(3 * 16, 0);
    topBun4->setScale(2, 2);

    auto lettuce1 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*lettuce1, BT_sprites::Sprite::LETTUCE_1);
    lettuce1->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce1->setScale(2, 2);

    auto lettuce2 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*lettuce2, BT_sprites::Sprite::LETTUCE_2);
    lettuce2->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce2->move(16, 0);
    lettuce2->setScale(2, 2);

    auto lettuce3 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*lettuce3, BT_sprites::Sprite::LETTUCE_3);
    lettuce3->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce3->move(2 * 16, 0);
    lettuce3->setScale(2, 2);

    auto lettuce4 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*lettuce4, BT_sprites::Sprite::LETTUCE_4);
    lettuce4->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce4->move(3 * 16, 0);
    lettuce4->setScale(2, 2);

    auto cheese1 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*cheese1, BT_sprites::Sprite::CHEESE_1);
    cheese1->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese1->setScale(2, 2);

    auto cheese2 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*cheese2, BT_sprites::Sprite::CHEESE_2);
    cheese2->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese2->move(16, 0);
    cheese2->setScale(2, 2);

    auto cheese3 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*cheese3, BT_sprites::Sprite::CHEESE_3);
    cheese3->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese3->move(2 * 16, 0);
    cheese3->setScale(2, 2);

    auto cheese4 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*cheese4, BT_sprites::Sprite::CHEESE_4);
    cheese4->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese4->move(3 * 16, 0);
    cheese4->setScale(2, 2);


    auto burger1 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*burger1, BT_sprites::Sprite::BURGER_1);
    burger1->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger1->setScale(2, 2);

    auto burger2 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*burger2, BT_sprites::Sprite::BURGER_2);
    burger2->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger2->move(16, 0);
    burger2->setScale(2, 2);

    auto burger3 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*burger3, BT_sprites::Sprite::BURGER_3);
    burger3->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger3->move(2 * 16, 0);
    burger3->setScale(2, 2);

    auto burger4 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*burger4, BT_sprites::Sprite::BURGER_4);
    burger4->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger4->move(3 * 16, 0);
    burger4->setScale(2, 2);

    auto tomato1 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*tomato1, BT_sprites::Sprite::TOMATO_1);
    tomato1->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato1->setScale(2, 2);

    auto tomato2 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*tomato2, BT_sprites::Sprite::TOMATO_2);
    tomato2->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato2->move(16, 0);
    tomato2->setScale(2, 2);

    auto tomato3 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*tomato3, BT_sprites::Sprite::TOMATO_3);
    tomato3->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato3->move(2 * 16, 0);
    tomato3->setScale(2, 2);

    auto tomato4 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*tomato4, BT_sprites::Sprite::TOMATO_4);
    tomato4->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato4->move(3 * 16, 0);
    tomato4->setScale(2, 2);

    auto botBun1 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*botBun1, BT_sprites::Sprite::BOTTOM_BREAD_1);
    botBun1->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    botBun1->setScale(2, 2);

    auto botBun2 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*botBun2, BT_sprites::Sprite::BOTTOM_BREAD_2);
    botBun2->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    botBun2->move(16, 0);
    botBun2->setScale(2, 2);

    auto botBun3 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*botBun3, BT_sprites::Sprite::BOTTOM_BREAD_3);
    botBun3->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    botBun3->move(2 * 16, 0);
    botBun3->setScale(2, 2);

    auto botBun4 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*botBun4, BT_sprites::Sprite::BOTTOM_BREAD_4);
    botBun4->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    botBun4->move(3 * 16, 0);
    botBun4->setScale(2, 2);


    auto fiftyPtsText = std::make_shared<sf::Text>();
    fiftyPtsText->setFillColor(sf::Color::White);
    fiftyPtsText->setScale(0.70, 0.70);
    fiftyPtsText->setFont(controller.font);
    fiftyPtsText->setString("50 PTS");
    fiftyPtsText->setPosition(67 * WINDOW_WIDTH / 100, 41 * WINDOW_HEIGHT / 100);

    auto iceCream = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*iceCream, BT_sprites::Sprite::ICE_CREAM);
    iceCream->setPosition(20 * WINDOW_WIDTH / 100, 55 * WINDOW_HEIGHT / 100);
    iceCream->setScale(2, 2);

    auto pt500 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*pt500, BT_sprites::Sprite::P_500);
    pt500->setPosition(20 * WINDOW_WIDTH / 100, 62 * WINDOW_HEIGHT / 100);
    pt500->setScale(2, 2);

    auto coffee = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*coffee, BT_sprites::Sprite::COFFEE);
    coffee->setPosition(30 * WINDOW_WIDTH / 100, 55 * WINDOW_HEIGHT / 100);
    coffee->setScale(2, 2);

    auto pt1000 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*pt1000, BT_sprites::Sprite::P_1000);
    pt1000->setPosition(30 * WINDOW_WIDTH / 100, 62 * WINDOW_HEIGHT / 100);
    pt1000->setScale(2, 2);

    auto fries = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*fries, BT_sprites::Sprite::FRIES);
    fries->setPosition(40 * WINDOW_WIDTH / 100, 55 * WINDOW_HEIGHT / 100);
    fries->setScale(2, 2);

    auto pt1500 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*pt1500, BT_sprites::Sprite::P_1500);
    pt1500->setPosition(40 * WINDOW_WIDTH / 100, 62 * WINDOW_HEIGHT / 100);
    pt1500->setScale(2, 2);

    auto bonusPepperText = std::make_shared<sf::Text>();
    bonusPepperText->setFillColor(sf::Color::White);
    bonusPepperText->setScale(0.70, 0.70);
    bonusPepperText->setFont(controller.font);
    bonusPepperText->setString("-BONUS 1");
    bonusPepperText->setPosition(48 * WINDOW_WIDTH / 100, 58 * WINDOW_HEIGHT / 100);

    auto pepper = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*pepper, BT_sprites::Sprite::PEPPER);
    pepper->setPosition(80 * WINDOW_WIDTH / 100, 58 * WINDOW_HEIGHT / 100);
    pepper->setScale(2, 2);

    auto bonusLifeText = std::make_shared<sf::Text>();
    bonusLifeText->setFillColor(sf::Color::White);
    bonusLifeText->setScale(0.70, 0.70);
    bonusLifeText->setFont(controller.font);
    bonusLifeText->setString("BONUS  FOR EVERY 20000PTS");
    bonusLifeText->setPosition(3 * WINDOW_WIDTH / 100, 80 * WINDOW_HEIGHT / 100);

    auto chef = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*chef, BT_sprites::Sprite::PLAYER_STILL_FRONT);
    chef->setPosition(22 * WINDOW_WIDTH / 100, 78 * WINDOW_HEIGHT / 100);
    chef->setScale(2, 2);

    controller.drawablesOnScreen.push_back(burgerTimeText);
    controller.drawablesOnScreen.push_back(scoreText);
    controller.drawablesOnScreen.push_back(topBun1);
    controller.drawablesOnScreen.push_back(topBun2);
    controller.drawablesOnScreen.push_back(topBun3);
    controller.drawablesOnScreen.push_back(topBun4);
    controller.drawablesOnScreen.push_back(lettuce1);
    controller.drawablesOnScreen.push_back(lettuce2);
    controller.drawablesOnScreen.push_back(lettuce3);
    controller.drawablesOnScreen.push_back(lettuce4);
    controller.drawablesOnScreen.push_back(cheese1);
    controller.drawablesOnScreen.push_back(cheese2);
    controller.drawablesOnScreen.push_back(cheese3);
    controller.drawablesOnScreen.push_back(cheese4);
    controller.drawablesOnScreen.push_back(burger1);
    controller.drawablesOnScreen.push_back(burger2);
    controller.drawablesOnScreen.push_back(burger3);
    controller.drawablesOnScreen.push_back(burger4);
    controller.drawablesOnScreen.push_back(tomato1);
    controller.drawablesOnScreen.push_back(tomato2);
    controller.drawablesOnScreen.push_back(tomato3);
    controller.drawablesOnScreen.push_back(tomato4);
    controller.drawablesOnScreen.push_back(botBun1);
    controller.drawablesOnScreen.push_back(botBun2);
    controller.drawablesOnScreen.push_back(botBun3);
    controller.drawablesOnScreen.push_back(botBun4);
    controller.drawablesOnScreen.push_back(fiftyPtsText);
    controller.drawablesOnScreen.push_back(iceCream);
    controller.drawablesOnScreen.push_back(pt500);
    controller.drawablesOnScreen.push_back(coffee);
    controller.drawablesOnScreen.push_back(pt1000);
    controller.drawablesOnScreen.push_back(fries);
    controller.drawablesOnScreen.push_back(pt1500);
    controller.drawablesOnScreen.push_back(bonusPepperText);
    controller.drawablesOnScreen.push_back(pepper);
    controller.drawablesOnScreen.push_back(bonusLifeText);
    controller.drawablesOnScreen.push_back(chef);
    controller.logicClock.restart();
}

void ItemPointsScreenState::entry()
{
    BurgerTimeStateMachine::itemPointsScreenStateEntry();
}

void ItemPointsScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact())
    {
        transit<CharacterScreenState>();
    }
}


void BurgerTimeStateMachine::characterScreenStateEntry()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Character Screen");

    controller.drawablesOnScreen.push_back(text);
    controller.logicClock.restart();
}

void CharacterScreenState::entry()
{
    BurgerTimeStateMachine::characterScreenStateEntry();
}

void CharacterScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact())
    {
        transit<FirstTutorialVidScreenState>();
    }
}


void BurgerTimeStateMachine::firstTutorialVidScreenStateEntry()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: First Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
    controller.logicClock.restart();
}

void FirstTutorialVidScreenState::entry()
{
    BurgerTimeStateMachine::firstTutorialVidScreenStateEntry();
}

void FirstTutorialVidScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact())
    {
        transit<SecondTutorialVidScreenState>();
    }
}


void BurgerTimeStateMachine::secondTutorialVidScreenStateEntry()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Second Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
    controller.logicClock.restart();
}

void SecondTutorialVidScreenState::entry()
{
    BurgerTimeStateMachine::secondTutorialVidScreenStateEntry();
}

void SecondTutorialVidScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact())
    {
        transit<TutorialScreenState>();
    }
}


void BurgerTimeStateMachine::tutorialScreenStateEntry()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Tutorial Screen");

    controller.drawablesOnScreen.push_back(text);
    controller.logicClock.restart();
}

void TutorialScreenState::entry()
{
    BurgerTimeStateMachine::tutorialScreenStateEntry();
}

void TutorialScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact())
    {
        transit<ThirdTutorialVidScreenState>();
    }
}


void BurgerTimeStateMachine::thirdTutorialVidScreenStateEntry()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: Third Tutorial Video");

    controller.drawablesOnScreen.push_back(text);
    controller.logicClock.restart();
}

void ThirdTutorialVidScreenState::entry()
{
    BurgerTimeStateMachine::thirdTutorialVidScreenStateEntry();
}

void ThirdTutorialVidScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact())
    {
        transit<MainScreenState>();
    }
}


void MainScreenState::entry()
{
    MainScreenStateMachine::reset();
    MainScreenStateMachine::start();
}

void MainScreenState::react(const ExecuteEvent &event)
{
    MainScreenStateMachine::dispatch(event);

    if (MainScreenStateMachine::is_in_state<FinishedStartState>())
    {
        transit<GameReadyScreenState>();
    }

    if (MainScreenStateMachine::is_in_state<FinishedExitState>())
    {
        transit<FinishedState>();
    }
}


void BurgerTimeStateMachine::gameReadyScreenState()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("GAME READY");
    text->setScale(0.8, 0.8);
    text->setPosition(30 * WINDOW_WIDTH / 100 , WINDOW_HEIGHT / 2);

    controller.drawablesOnScreen.push_back(text);
    controller.logicClock.restart();
}

void GameReadyScreenState::entry()
{
    BurgerTimeStateMachine::gameReadyScreenState();
}

void GameReadyScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact())
    {
        // TODO: change
        transit<PlayingState>();
        // transit<EnterHighscoreState>(std::bind(&EnterHighscoreState::setHighScore, 999999));
    }
}


void PlayingState::entry()
{
    PlayingStateMachine::reset();
    PlayingStateMachine::start();
}

void PlayingState::react(const ExecuteEvent &event)
{
    PlayingStateMachine::dispatch(event);

    // if (MainScreenStateMachine::is_in_state<FinishedStartState>())
    // {
    //     transit<GameReadyScreenState>();
    // }

    // if (MainScreenStateMachine::is_in_state<FinishedExitState>())
    // {
    //     transit<FinishedState>();
    // }
}


constexpr std::array<const char*, GameOverScreenState::MAX_TEXTS> GameOverScreenState::DIFFERENT_TEXTS;

void GameOverScreenState::entry()
{
    controller.drawablesOnScreen.clear();

    text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString(DIFFERENT_TEXTS[0]);
    text->setScale(0.8, 0.8);
    text->setPosition(30 * WINDOW_WIDTH / 100 , WINDOW_HEIGHT / 2);

    controller.drawablesOnScreen.push_back(text);
    currentText = 1;
    controller.logicClock.restart();
}

void GameOverScreenState::react(const ExecuteEvent &)
{
    auto elapsedTime = controller.logicClock.getElapsedTime();

    if (currentText == MAX_TEXTS)
    {
        if (elapsedTime.asSeconds() >= 1)
        {
            // TODO: change
            transit<MainScreenState>();
            return;
        }
    }
    else if (elapsedTime.asSeconds() >= ANIMATION_FREQ)
    {
        text->setString(DIFFERENT_TEXTS[currentText]);
        currentText++;
        controller.logicClock.restart();
    }
}


uint32_t EnterHighscoreState::newHighscore;

void EnterHighscoreState::entry()
{
    controller.drawablesOnScreen.clear();

    newHighScoreText = std::make_shared<sf::Text>();

    auto burgerTimeText = std::make_shared<sf::Text>();
    burgerTimeText->setFillColor(sf::Color::Red);
    burgerTimeText->setScale(0.70, 0.70);
    burgerTimeText->setFont(controller.font);
    burgerTimeText->setString("BURGER TIME");
    burgerTimeText->setPosition(28 * WINDOW_WIDTH / 100, 15 * WINDOW_HEIGHT / 100);

    helpText = std::make_shared<sf::Text>();
    helpText->setFillColor(sf::Color::White);
    helpText->setScale(0.70, 0.70);
    helpText->setFont(controller.font);
    helpText->setString(ENTER_NAME_STR);
    helpText->setPosition(22 * WINDOW_WIDTH / 100, 30 * WINDOW_HEIGHT / 100);

    HighScores highScores("welp.hscores");
    auto hScores = highScores.getHighScores();

    int highScorePosition = highScores.highScorePosition(newHighscore);
    bool hasWrittenNewScore = false;

    for (int i = 0; i < HighScores::NUM_HIGH_SCORES; ++i)
    {
        uint32_t highScore;
        std::string playerName;
        std::shared_ptr<sf::Text> hScoreText;
        if (i + 1 == highScorePosition)
        {
            hScoreText = newHighScoreText;
            highScore = newHighscore;
            playerName = "_  ";
            hasWrittenNewScore = true;
        }
        else
        {
            int pos = i;
            if (hasWrittenNewScore)
            {
                pos -= 1;
            }
            hScoreText = std::make_shared<sf::Text>();
            highScore = hScores[pos].second;
            playerName = hScores[pos].first.data();
        }

        auto scoreStr = std::to_string(highScore);
        std::string whiteSpace(" ");

        for (uint8_t j = 0; j < HighScores::MAX_SCORE_CHARS - scoreStr.length(); ++j)
        {
            whiteSpace += " ";
        }

        hScoreText->setFillColor(sf::Color::White);
        hScoreText->setScale(0.70, 0.70);
        hScoreText->setFont(controller.font);
        hScoreText->setString(std::to_string(i + 1) + " " + playerName + whiteSpace + scoreStr + " PTS");
        hScoreText->setPosition(18 * WINDOW_WIDTH / 100, (45 + i * 10) * WINDOW_HEIGHT / 100);
        controller.drawablesOnScreen.push_back(hScoreText);
    }

    controller.drawablesOnScreen.push_back(burgerTimeText);
    controller.drawablesOnScreen.push_back(helpText);
    controller.logicClock.restart();
}

void EnterHighscoreState::react(const ExecuteEvent &)
{
    auto currentStr = newHighScoreText->getString();
    if (charPosition > 0 && InputSystem::hasInputJustBeenPressed(InputSystem::Input::DELETE))
    {
        if (charPosition < HighScores::PLAYER_NAME_SIZE - 1)
        {
            currentStr[2 + charPosition] = ' ';
        }
        charPosition--;
        currentStr[2 + charPosition] = '_';
    }

    if (charPosition < HighScores::PLAYER_NAME_SIZE - 1 && InputSystem::hasEnteredText())
    {
        char newChar = InputSystem::getCurrentChar();
        currentStr[2 + charPosition] = newChar;
        if (charPosition < HighScores::PLAYER_NAME_SIZE - 2)
        {
            currentStr[2 + charPosition + 1] = '_';
        }
        charPosition++;
    }

    if (charPosition == HighScores::PLAYER_NAME_SIZE - 1)
    {
        helpText->setString("CONFIRM? (PEPPER)");
        helpText->setPosition(18 * WINDOW_WIDTH / 100, 30 * WINDOW_HEIGHT / 100);
        if (InputSystem::hasInputJustBeenPressed(InputSystem::Input::PEPPER))
        {
            // TODO: save new highscores etc etc
            transit<MainScreenState>();
        }
    }
    else
    {
        helpText->setString(ENTER_NAME_STR);
        helpText->setPosition(22 * WINDOW_WIDTH / 100, 30 * WINDOW_HEIGHT / 100);
    }
    

    newHighScoreText->setString(currentStr);
}

void EnterHighscoreState::setHighScore(uint32_t highScore)
{
    newHighscore = highScore;
}
