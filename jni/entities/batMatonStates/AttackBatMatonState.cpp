#include "AttackBatMatonState.h"

AttackBatMatonState::AttackBatMatonState(BatBot* bat)
:BatBot::BatAutomatonState::BatAutomatonState(bat)
{

	player = bat->levelData->GetEntityByID("character0");
    maxTime = 2; //Attack for 2 seconds.
}

void AttackBatMatonState::Execute(float t_elapsed)
{
    bat->vel.ScaleAdd(t_elapsed*2.0, bat->attackVector);

    mjVector3 batToPlayer;
    batToPlayer.CopyFrom(player->pos);
    batToPlayer.Subtract(bat->pos);
    float distToPlayer = batToPlayer.Normalize();

	if ((distToPlayer < bat->attackDistance) && (bat->dir.Dot(bat->attackVector) < M_PI))
    {
        destStateOnTimeExpiration = BM_DETECT;

    } else
    {
        destStateOnTimeExpiration = BM_WANDER;
    }
}

AttackBatMatonState::~AttackBatMatonState()
{
    //dtor
}
