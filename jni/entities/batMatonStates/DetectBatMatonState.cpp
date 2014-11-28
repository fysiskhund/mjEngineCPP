#include "DetectBatMatonState.h"

DetectBatMatonState::DetectBatMatonState(BatBot* bat)
:BatBot::BatAutomatonState::BatAutomatonState(bat)
{

	player = bat->levelData->GetEntityByID("character0");

}
void DetectBatMatonState::Reset()
{
    BatBot::BatAutomatonState::Reset();
    maxTime = -1;
}

void DetectBatMatonState::Execute(float t_elapsed)
{
    bat->attackVector.CopyFrom(player->pos);
    bat->attackVector.Subtract(bat->pos);

    float distToPlayer = bat->attackVector.Normalize();

    bat->dir.CopyFrom(bat->attackVector);
    bat->dir.y = 0;
    bat->dir.Normalize();

	if (distToPlayer > bat->attackDistance)
    {
        destStateOnTimeExpiration = 0;
        maxTime = 0.5;

    }
}


DetectBatMatonState::~DetectBatMatonState()
{
    //dtor
}
