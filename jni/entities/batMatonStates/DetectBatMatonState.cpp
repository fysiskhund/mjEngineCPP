#include "DetectBatMatonState.h"

DetectBatMatonState::DetectBatMatonState(BatBot* bat)
:BatBot::BatAutomatonState::BatAutomatonState(bat)
{

	player = bat->levelData->GetEntityByID("character0");
    destStateOnTimeExpiration = 3;
    maxTime = 2;
}
void DetectBatMatonState::Reset()
{
    BatBot::BatAutomatonState::Reset();


}

void DetectBatMatonState::Execute(float t_elapsed)
{
    bat->attackVector.CopyFrom(player->pos);
    bat->attackVector.Subtract(bat->pos);

    float distToPlayer = bat->attackVector.Normalize();

    bat->dir.CopyFrom(bat->attackVector);
    bat->dir.y = 0;
    bat->dir.Normalize();


}


DetectBatMatonState::~DetectBatMatonState()
{
    //dtor
}
