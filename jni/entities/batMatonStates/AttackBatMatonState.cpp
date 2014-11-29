#include "AttackBatMatonState.h"

AttackBatMatonState::AttackBatMatonState(BatBot* bat)
:BatBot::BatAutomatonState::BatAutomatonState(bat)
{

	player = bat->levelData->GetEntityByID("character0");
    //ctor
}

AttackBatMatonState::~AttackBatMatonState()
{
    //dtor
}
