#include "BurgerTimeStateMachine.hpp"

#include <memory>
#include <string>
// #include <functional>
#include <SFML/Graphics.hpp>
#include "InputSystem.hpp"
#include "MainScreenStateMachine.hpp"
#include "PlayingStateMachine.hpp"
#include "BT_sprites.hpp"


FSM_INITIAL_STATE(BurgerTimeStateMachine, HighscoreDisplayScreenState)

BurgerTimeController &BurgerTimeStateMachine::controller = BurgerTimeController::get();
GUI &BurgerTimeStateMachine::gui = GUI::get();


bool BurgerTimeStateMachine::timedStateReact(int waitTime)
{
    if (hasInputJustBeenPressed(InputSystem::Input::PAUSE))
    {
        controller.restartTimer();
        return true;
    }

    auto elapsedTime = controller.getElapsedTime();
    if (elapsedTime.asSeconds() >= waitTime)
    {
        controller.restartTimer();
        return true;
    }

    return false;
}


void HighscoreDisplayScreenState::entry()
{
    controller.clearScreen();

    auto burgerTimeText = gui.createText("hScoreBurTime", "BURGER TIME", sf::Vector2u(280, 150), sf::Vector2f(0.70, 0.70), sf::Color::Red);
    auto bestFivePlayersText = gui.createText("hScoreBestFivePlayers", "BEST FIVE PLAYERS", sf::Vector2u(180, 300), sf::Vector2f(0.70, 0.70));


    HighScores highScores("welp.hscores");
    auto hScores = highScores.getHighScores();

    for (int i = 0; i < HighScores::NUM_HIGH_SCORES; ++i)
    {
        auto scoreStr = std::to_string(hScores[i].second);

        std::string text = std::to_string(i + 1) + " " + hScores[i].first.data() + GUI::fixTextToRight(scoreStr, MAX_SCORE_CHARS) + " PTS";
        auto hScoreText = gui.createText(std::string("hScorehScoreText") + std::to_string(i), text, sf::Vector2u(180, (450 + i * 100)), sf::Vector2f(0.70, 0.70));

        controller.addDrawable(hScoreText);
    }

    controller.addDrawable(burgerTimeText);
    controller.addDrawable(bestFivePlayersText);
    controller.restartTimer();
}

void HighscoreDisplayScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact(5))
    {
        transit<ItemPointsScreenState>();
    }
}


void ItemPointsScreenState::entry()
{
    // TODO: change magic numbers to constants and mb reduce code size

    controller.clearScreen();

    auto burgerTimeText = gui.createText("itemPointsBurTime", "BURGER TIME", sf::Vector2u(280, 150), sf::Vector2f(0.70, 0.70), sf::Color::Red);

    auto scoreText = gui.createText("itemPointsScore", "-SCORE-", sf::Vector2u(340, 230), sf::Vector2f(0.70, 0.70));

    topBun[0] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*topBun[0], BT_sprites::Sprite::TOP_BREAD_1);
    topBun[0]->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    topBun[0]->setScale(2, 2);

    topBun[1] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*topBun[1], BT_sprites::Sprite::TOP_BREAD_2);
    topBun[1]->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    topBun[1]->move(16, 0);
    topBun[1]->setScale(2, 2);

    topBun[2] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*topBun[2], BT_sprites::Sprite::TOP_BREAD_3);
    topBun[2]->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    topBun[2]->move(2 * 16, 0);
    topBun[2]->setScale(2, 2);

    topBun[3] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*topBun[3], BT_sprites::Sprite::TOP_BREAD_4);
    topBun[3]->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    topBun[3]->move(3 * 16, 0);
    topBun[3]->setScale(2, 2);

    lettuce[0] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*lettuce[0], BT_sprites::Sprite::LETTUCE_1);
    lettuce[0]->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce[0]->setScale(2, 2);

    lettuce[1] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*lettuce[1], BT_sprites::Sprite::LETTUCE_2);
    lettuce[1]->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce[1]->move(16, 0);
    lettuce[1]->setScale(2, 2);

    lettuce[2] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*lettuce[2], BT_sprites::Sprite::LETTUCE_3);
    lettuce[2]->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce[2]->move(2 * 16, 0);
    lettuce[2]->setScale(2, 2);

    lettuce[3] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*lettuce[3], BT_sprites::Sprite::LETTUCE_4);
    lettuce[3]->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce[3]->move(3 * 16, 0);
    lettuce[3]->setScale(2, 2);

    cheese[0] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*cheese[0], BT_sprites::Sprite::CHEESE_1);
    cheese[0]->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese[0]->setScale(2, 2);

    cheese[1] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*cheese[1], BT_sprites::Sprite::CHEESE_2);
    cheese[1]->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese[1]->move(16, 0);
    cheese[1]->setScale(2, 2);

    cheese[2] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*cheese[2], BT_sprites::Sprite::CHEESE_3);
    cheese[2]->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese[2]->move(2 * 16, 0);
    cheese[2]->setScale(2, 2);

    cheese[3] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*cheese[3], BT_sprites::Sprite::CHEESE_4);
    cheese[3]->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese[3]->move(3 * 16, 0);
    cheese[3]->setScale(2, 2);


    burger[0] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*burger[0], BT_sprites::Sprite::BURGER_1);
    burger[0]->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger[0]->setScale(2, 2);

    burger[1] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*burger[1], BT_sprites::Sprite::BURGER_2);
    burger[1]->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger[1]->move(16, 0);
    burger[1]->setScale(2, 2);

    burger[2] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*burger[2], BT_sprites::Sprite::BURGER_3);
    burger[2]->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger[2]->move(2 * 16, 0);
    burger[2]->setScale(2, 2);

    burger[3] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*burger[3], BT_sprites::Sprite::BURGER_4);
    burger[3]->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger[3]->move(3 * 16, 0);
    burger[3]->setScale(2, 2);

    tomato[0] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*tomato[0], BT_sprites::Sprite::TOMATO_1);
    tomato[0]->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato[0]->setScale(2, 2);

    tomato[1] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*tomato[1], BT_sprites::Sprite::TOMATO_2);
    tomato[1]->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato[1]->move(16, 0);
    tomato[1]->setScale(2, 2);

    tomato[2] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*tomato[2], BT_sprites::Sprite::TOMATO_3);
    tomato[2]->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato[2]->move(2 * 16, 0);
    tomato[2]->setScale(2, 2);

    tomato[3] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*tomato[3], BT_sprites::Sprite::TOMATO_4);
    tomato[3]->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato[3]->move(3 * 16, 0);
    tomato[3]->setScale(2, 2);

    botBun[0] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*botBun[0], BT_sprites::Sprite::BOTTOM_BREAD_1);
    botBun[0]->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    botBun[0]->setScale(2, 2);

    botBun[1] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*botBun[1], BT_sprites::Sprite::BOTTOM_BREAD_2);
    botBun[1]->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    botBun[1]->move(16, 0);
    botBun[1]->setScale(2, 2);

    botBun[2] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*botBun[2], BT_sprites::Sprite::BOTTOM_BREAD_3);
    botBun[2]->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    botBun[2]->move(2 * 16, 0);
    botBun[2]->setScale(2, 2);

    botBun[3] = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*botBun[3], BT_sprites::Sprite::BOTTOM_BREAD_4);
    botBun[3]->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    botBun[3]->move(3 * 16, 0);
    botBun[3]->setScale(2, 2);


    auto fiftyPtsText = gui.createText("itemPointsFiftyPts", "50 PTS", sf::Vector2u(670, 410), sf::Vector2f(0.70, 0.70));

    iceCream = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*iceCream, BT_sprites::Sprite::ICE_CREAM);
    iceCream->setPosition(20 * WINDOW_WIDTH / 100, 55 * WINDOW_HEIGHT / 100);
    iceCream->setScale(2, 2);

    pt500 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*pt500, BT_sprites::Sprite::P_500);
    pt500->setPosition(20 * WINDOW_WIDTH / 100, 62 * WINDOW_HEIGHT / 100);
    pt500->setScale(2, 2);

    coffee = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*coffee, BT_sprites::Sprite::COFFEE);
    coffee->setPosition(30 * WINDOW_WIDTH / 100, 55 * WINDOW_HEIGHT / 100);
    coffee->setScale(2, 2);

    pt1000 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*pt1000, BT_sprites::Sprite::P_1000);
    pt1000->setPosition(30 * WINDOW_WIDTH / 100, 62 * WINDOW_HEIGHT / 100);
    pt1000->setScale(2, 2);

    fries = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*fries, BT_sprites::Sprite::FRIES);
    fries->setPosition(40 * WINDOW_WIDTH / 100, 55 * WINDOW_HEIGHT / 100);
    fries->setScale(2, 2);

    pt1500 = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*pt1500, BT_sprites::Sprite::P_1500);
    pt1500->setPosition(40 * WINDOW_WIDTH / 100, 62 * WINDOW_HEIGHT / 100);
    pt1500->setScale(2, 2);

    auto bonusPepperText = gui.createText("itemPointsBonusPepper", "-BONUS 1", sf::Vector2u(480, 580), sf::Vector2f(0.70, 0.70));

    pepper = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*pepper, BT_sprites::Sprite::PEPPER);
    pepper->setPosition(80 * WINDOW_WIDTH / 100, 58 * WINDOW_HEIGHT / 100);
    pepper->setScale(2, 2);

    auto bonusLifeText = gui.createText("itemPointsBonusLife", "BONUS  FOR EVERY 20000PTS", sf::Vector2u(30, 800), sf::Vector2f(0.70, 0.70));

    chef = std::make_shared<sf::Sprite>();
    BT_sprites::set_initial_sprite(*chef, BT_sprites::Sprite::PLAYER_STILL_FRONT);
    chef->setPosition(22 * WINDOW_WIDTH / 100, 78 * WINDOW_HEIGHT / 100);
    chef->setScale(2, 2);

    controller.addDrawable(burgerTimeText);
    controller.addDrawable(scoreText);
    controller.addDrawable(topBun[0]);
    controller.addDrawable(topBun[1]);
    controller.addDrawable(topBun[2]);
    controller.addDrawable(topBun[3]);
    controller.addDrawable(lettuce[0]);
    controller.addDrawable(lettuce[1]);
    controller.addDrawable(lettuce[2]);
    controller.addDrawable(lettuce[3]);
    controller.addDrawable(cheese[0]);
    controller.addDrawable(cheese[1]);
    controller.addDrawable(cheese[2]);
    controller.addDrawable(cheese[3]);
    controller.addDrawable(burger[0]);
    controller.addDrawable(burger[1]);
    controller.addDrawable(burger[2]);
    controller.addDrawable(burger[3]);
    controller.addDrawable(tomato[0]);
    controller.addDrawable(tomato[1]);
    controller.addDrawable(tomato[2]);
    controller.addDrawable(tomato[3]);
    controller.addDrawable(botBun[0]);
    controller.addDrawable(botBun[1]);
    controller.addDrawable(botBun[2]);
    controller.addDrawable(botBun[3]);
    controller.addDrawable(fiftyPtsText);
    controller.addDrawable(iceCream);
    controller.addDrawable(pt500);
    controller.addDrawable(coffee);
    controller.addDrawable(pt1000);
    controller.addDrawable(fries);
    controller.addDrawable(pt1500);
    controller.addDrawable(bonusPepperText);
    controller.addDrawable(pepper);
    controller.addDrawable(bonusLifeText);
    controller.addDrawable(chef);
    controller.restartTimer();
}

void ItemPointsScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact(5))
    {
        transit<CharacterScreenState>();
    }
}


void CharacterScreenState::entry()
{
    controller.clearScreen();

    auto text = gui.createText("characterTODO", "TODO: Character Screen");

    controller.addDrawable(text);
    controller.restartTimer();
}

void CharacterScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact(5))
    {
        transit<FirstTutorialVidScreenState>();
    }
}


void FirstTutorialVidScreenState::entry()
{
    controller.clearScreen();

    auto text = gui.createText("firstTutorialVidTODO", "TODO: First Tutorial Video");

    controller.addDrawable(text);
    controller.restartTimer();
}

void FirstTutorialVidScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact(5))
    {
        transit<SecondTutorialVidScreenState>();
    }
}


void SecondTutorialVidScreenState::entry()
{
    controller.clearScreen();

    auto text = gui.createText("secondTutorialVidTODO", "TODO: Second Tutorial Video");

    controller.addDrawable(text);
    controller.restartTimer();
}

void SecondTutorialVidScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact(5))
    {
        transit<TutorialScreenState>();
    }
}


void TutorialScreenState::entry()
{
    controller.clearScreen();

    auto text = gui.createText("tutorialScreenTODO", "TODO: Tutorial Screen");

    controller.addDrawable(text);
    controller.restartTimer();
}

void TutorialScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact(5))
    {
        transit<ThirdTutorialVidScreenState>();
    }
}


void ThirdTutorialVidScreenState::entry()
{
    controller.clearScreen();

    auto text = gui.createText("thirdTutorialVidTODO", "TODO: Third Tutorial Video");

    controller.addDrawable(text);
    controller.restartTimer();
}

void ThirdTutorialVidScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact(5))
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
        transit<PlayingState>();
    }

    if (MainScreenStateMachine::is_in_state<FinishedExitState>())
    {
        transit<FinishedState>();
    }
}


void PlayingState::entry()
{
    PlayingStateMachine::reset();
    PlayingStateMachine::start();
}

void PlayingState::react(const ExecuteEvent &event)
{
    if (PlayingStateMachine::is_in_state<GameOverStatePlaying>())
    {
        transit<GameOverScreenState>();
    }
    else
    {
        PlayingStateMachine::dispatch(event);
    }
    // TODO: mas
}


constexpr std::array<const char*, GameOverScreenState::MAX_TEXTS> GameOverScreenState::DIFFERENT_TEXTS;

void GameOverScreenState::entry()
{
    controller.clearScreen();

    auto text = gui.createText("gameOverText", DIFFERENT_TEXTS[0], sf::Vector2u(300, 500), sf::Vector2f(0.8, 0.8));

    controller.addDrawable(text);
    currentText = 1;
    controller.restartTimer();
}

void GameOverScreenState::react(const ExecuteEvent &)
{
    auto elapsedTime = controller.getElapsedTime();

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
        auto text = gui.getText("gameOverText").lock();
        text->setString(DIFFERENT_TEXTS[currentText]);
        currentText++;
        controller.restartTimer();
    }
}


// uint32_t EnterHighscoreState::newHighscore;

// void EnterHighscoreState::entry()
// {
//     controller.clearScreen();

//     auto burgerTimeText = gui.createText("enterHighScoreBurTime", "BURGER TIME", sf::Vector2u(280, 150), sf::Vector2f(0.7, 0.7), sf::Color::Red);

//     auto helpText = gui.createText("enterHighScoreHelp", ENTER_NAME_STR, sf::Vector2u(220, 300), sf::Vector2f(0.7, 0.7));

//     HighScores highScores("welp.hscores");
//     auto hScores = highScores.getHighScores();

//     int highScorePosition = highScores.highScorePosition(newHighscore);
//     bool hasWrittenNewScore = false;

//     for (int i = 0; i < HighScores::NUM_HIGH_SCORES; ++i)
//     {
//         uint32_t highScore;
//         std::string playerName;
//         std::weak_ptr<sf::Text> hScoreText;
//         if (i + 1 == highScorePosition)
//         {
//             hScoreTexts[i] = newHighScoreText;
//             highScore = newHighscore;
//             playerName = "_  ";
//             hasWrittenNewScore = true;
//         }
//         else
//         {
//             int pos = i;
//             if (hasWrittenNewScore)
//             {
//                 pos -= 1;
//             }
//             hScoreTexts[i] = std::make_shared<sf::Text>();
//             highScore = hScores[pos].second;
//             playerName = hScores[pos].first.data();
//         }

//         auto scoreStr = std::to_string(highScore);
//         std::string whiteSpace(" ");

//         for (uint8_t j = 0; j < MAX_SCORE_CHARS - scoreStr.length(); ++j)
//         {
//             whiteSpace += " ";
//         }

//         hScoreTexts[i]->setFillColor(sf::Color::White);
//         hScoreTexts[i]->setScale(0.70, 0.70);
//         hScoreTexts[i]->setFont(controller.font);
//         hScoreTexts[i]->setString(std::to_string(i + 1) + " " + playerName + whiteSpace + scoreStr + " PTS");
//         hScoreTexts[i]->setPosition(18 * WINDOW_WIDTH / 100, (45 + i * 10) * WINDOW_HEIGHT / 100);
//         controller.addDrawable(hScoreTexts[i]);
//     }

//     controller.addDrawable(burgerTimeText);
//     controller.addDrawable(helpText);
//     controller.restartTimer();
// }

// void EnterHighscoreState::react(const ExecuteEvent &)
// {
//     auto currentStr = newHighScoreText->getString();
//     if (charPosition > 0 && InputSystem::hasInputJustBeenPressed(InputSystem::Input::DELETE))
//     {
//         if (charPosition < HighScores::PLAYER_NAME_SIZE - 1)
//         {
//             currentStr[2 + charPosition] = ' ';
//         }
//         charPosition--;
//         currentStr[2 + charPosition] = '_';
//     }

//     if (charPosition < HighScores::PLAYER_NAME_SIZE - 1 && InputSystem::hasEnteredText())
//     {
//         char newChar = InputSystem::getCurrentChar();
//         currentStr[2 + charPosition] = newChar;
//         if (charPosition < HighScores::PLAYER_NAME_SIZE - 2)
//         {
//             currentStr[2 + charPosition + 1] = '_';
//         }
//         charPosition++;
//     }

//     if (charPosition == HighScores::PLAYER_NAME_SIZE - 1)
//     {
//         helpText->setString("CONFIRM? (PEPPER)");
//         helpText->setPosition(18 * WINDOW_WIDTH / 100, 30 * WINDOW_HEIGHT / 100);
//         if (InputSystem::hasInputJustBeenPressed(InputSystem::Input::PEPPER))
//         {
//             // TODO: save new highscores etc etc
//             transit<MainScreenState>();
//         }
//     }
//     else
//     {
//         helpText->setString(ENTER_NAME_STR);
//         helpText->setPosition(22 * WINDOW_WIDTH / 100, 30 * WINDOW_HEIGHT / 100);
//     }
    

//     newHighScoreText->setString(currentStr);
// }

// void EnterHighscoreState::setHighScore(uint32_t highScore)
// {
//     newHighscore = highScore;
// }
