#include "PlayingStateMachine.hpp"
#include "InputSystem.hpp"

FSM_INITIAL_STATE(PlayingStateMachine, EnterStatePlaying)

BurgerTimeController &PlayingStateMachine::controller = BurgerTimeController::get();

void PlayingStateMachine::enterStateEntry()
{
    controller.drawablesOnScreen.clear();

    Map *map = new Map("maps/only_floor.map");
    mapView = std::make_shared<MapView>(map);
    player = std::make_shared<Player>(Vector2f(70, 90), mapView);

    controller.drawablesOnScreen.push_back(mapView);
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
