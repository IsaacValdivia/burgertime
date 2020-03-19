#include "PlayingStateMachine.hpp"
#include "InputSystem.hpp"

FSM_INITIAL_STATE(PlayingStateMachine, EnterStatePlaying)

BurgerTimeController &PlayingStateMachine::controller = BurgerTimeController::get();

void PlayingStateMachine::enterStateEntry()
{
    controller.drawablesOnScreen.clear();

    map = std::make_shared<Map>("maps/map1.map");
    player = std::make_shared<Player>(map->data[0][4].shape.getPosition(), map);

    controller.drawablesOnScreen.push_back(map);
    controller.drawablesOnScreen.push_back(player);
}

void EnterStatePlaying::entry()
{
    PlayingStateMachine::enterStateEntry();
}

void EnterStatePlaying::react(const ExecuteEvent &event)
{
    player->update(event.deltaT);
    // player->win();
    // transit<StartOptionState>();
}
