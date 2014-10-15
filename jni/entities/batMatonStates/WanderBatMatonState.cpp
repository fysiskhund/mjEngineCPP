#include "WanderBatMatonState.h"

WanderBatMatonState::WanderBatMatonState(BatBot* bat)
:BatBot::BatAutomatonState::BatAutomatonState(bat)
{
	player = bat->levelData->GetEntityByID("character0");

}

void WanderBatMatonState::Execute(float t_elapsed)
{

	if (player)
	{

	}
}
