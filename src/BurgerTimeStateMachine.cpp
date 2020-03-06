#include "BurgerTimeStateMachine.hpp"

#include <memory>
#include <SFML/Graphics.hpp>
#include "BurgerTimeController.hpp"
#include "InputSystem.hpp"
#include "MainScreenStateMachine.hpp"


FSM_INITIAL_STATE(BurgerTimeStateMachine, HighscoreDisplayScreenState)

static BurgerTimeController &controller = BurgerTimeController::get();


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
    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("TODO: High Score Screen");

    controller.drawablesOnScreen.push_back(text);
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
    controller.drawablesOnScreen.clear();

    auto burgerTimeText = std::make_shared<sf::Text>();
    burgerTimeText->setFillColor(sf::Color::Red);
    burgerTimeText->setFont(controller.font);
    burgerTimeText->setString("BURGER TIME");
    burgerTimeText->setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4);

    auto todoText = std::make_shared<sf::Text>();
    todoText->setFont(controller.font);
    todoText->setString("TODO: item points screen");
    todoText->setPosition(WINDOW_WIDTH / 5, WINDOW_HEIGHT / 3);

    controller.drawablesOnScreen.push_back(burgerTimeText);
    controller.drawablesOnScreen.push_back(todoText);
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

void MainScreenState::react(const ExecuteEvent &)
{
    MainScreenStateMachine::dispatch(ExecuteEvent());

    if (MainScreenStateMachine::is_in_state<FinishedStartState>())
    {
        transit<GameReadyScreenState>();
    }

    if (MainScreenStateMachine::is_in_state<FinishedExitState>())
    {
        //TODO
    }
}


void BurgerTimeStateMachine::gameReadyScreenState()
{
    controller.drawablesOnScreen.clear();

    auto text = std::make_shared<sf::Text>();

    text->setFont(controller.font);
    text->setString("GAME READY");
    text->setScale(0.8, 0.8);
    text->setPosition(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2);

    controller.drawablesOnScreen.push_back(text);
}

void GameReadyScreenState::entry()
{
    BurgerTimeStateMachine::gameReadyScreenState();
}

void GameReadyScreenState::react(const ExecuteEvent &)
{
    if (BurgerTimeStateMachine::timedStateReact())
    {
        // transit<ThirdTutorialVidScreenState>();
    }
}
