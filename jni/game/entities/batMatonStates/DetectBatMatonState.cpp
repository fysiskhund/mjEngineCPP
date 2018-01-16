#include "DetectBatMatonState.h"

DetectBatMatonState::DetectBatMatonState(BatBot* bat)
:BatBot::BatAutomatonState::BatAutomatonState(bat)
{

	player = bat->levelData->GetEntityByID("character0");
    destStateOnTimeExpiration = BM_ATTACK;
    maxTime = 0.8;


}
void DetectBatMatonState::Reset()
{
    BatBot::BatAutomatonState::Reset();


}

void DetectBatMatonState::Execute(double t_elapsed)
{
    bat->attackVector.CopyFrom(player->pos);
    bat->attackVector.Subtract(bat->pos);

    float distToPlayer = bat->attackVector.Normalize();

    bat->dir.CopyFrom(bat->attackVector);
    bat->dir.y = 0;
    bat->dir.Normalize();

    bat->vel.Set0();

    exciteAngle += 8.0*M_PI*t_elapsed;

    if (exciteAngle > 2.0*M_PI)
    {
        exciteAngle -= 2.0*M_PI;
    }

    bat->modelOffset.y = 0.2*sin(exciteAngle);


}


DetectBatMatonState::~DetectBatMatonState()
{
    //dtor
}
