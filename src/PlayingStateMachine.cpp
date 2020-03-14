#include "PlayingStateMachine.hpp"
#include "InputSystem.hpp"

FSM_INITIAL_STATE(PlayingStateMachine, EnterStatePlaying)

BurgerTimeController &PlayingStateMachine::controller = BurgerTimeController::get();

void PlayingStateMachine::enterStateEntry()
{
    controller.drawablesOnScreen.clear();

    Map *map = new Map("maps/map1.map");
    mapView = std::make_shared<MapView>(map);
    player = std::make_shared<Player>(Vector2f(10, 10));

    controller.drawablesOnScreen.push_back(mapView);
    controller.drawablesOnScreen.push_back(player);
}

void EnterStatePlaying::entry()
{
    PlayingStateMachine::enterStateEntry();
}

void EnterStatePlaying::react(const ExecuteEvent &)
{
    player->update(0.2);
    // transit<StartOptionState>();
}
