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
		bat->wanderDir.CopyFrom(player->pos);
		bat->wanderDir.Subtract(bat->pos);
		float norm = bat->wanderDir.Normalize();
		//bat->dir.CopyFrom(bat->wanderDir);
		//bat->dir.y = 0;


		if (norm > bat->wanderRadiusMin)
		{
			bat->pos.ScaleAdd(t_elapsed*WANDER_SPEED, bat->wanderDir);
		}
		//LOGI("BatWander->Execute; %3.3f, %3.3f, %3.3f", bat->pos.x, bat->pos.y, bat->pos.z);

	}
}
