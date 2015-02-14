#include "FrogJumpAutomatonState.h"

FrogAutomatonJumpState::FrogAutomatonJumpState(Frog* frog):
Frog::FrogAutomatonState::FrogAutomatonState(frog)
{
    destStateOnTimeExpiration = 0;

}

void FrogAutomatonJumpState::Enter()
{

    frog->jumpDirection.y = 2;

    frog->vel.CopyFrom(frog->jumpDirection);
    frog->soundSource->Play(frog->pos, 0);

    maxTime = 1; // Jump each 3 secnds
    //FIXME: change to detect frog has footing
}

void FrogAutomatonJumpState::Execute(float t_elapsed)
{
    if (mjCollisionTests::AABBVsAABB((mjAABB*)frog->boundingStructure, frog->levelData->hardLimits, NULL) == MJ_NO_COLLISION)
    {
        frog->pos.CopyFrom(frog->startPosition);
        frog->vel.Set0();
    }

}
