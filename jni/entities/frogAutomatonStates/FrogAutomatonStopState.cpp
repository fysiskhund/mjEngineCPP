#include "FrogAutomatonStopState.h"

FrogAutomatonStopState::FrogAutomatonStopState(Frog* frog):
Frog::FrogAutomatonState::FrogAutomatonState(frog)
{

    destStateOnTimeExpiration = 1;
}

void FrogAutomatonStopState::Enter()
{
    float theta = ((float)rand() / (float) RAND_MAX)*2.0*3.141592;

    frog->jumpDirection.Set(sin(theta), 0, cos(theta));
     maxTime = 3.0*((float)rand() / (float) RAND_MAX) + 0.5;
    frog->vel.Set0();
}


void FrogAutomatonStopState::Execute(float t_elapsed)
{
    if (mjCollisionTests::AABBVsAABB((mjAABB*) frog->boundingStructure, frog->levelData->hardLimits, NULL) != MJ_OVERLAP)
    {
        frog->pos.CopyFrom(frog->startPosition);
        frog->vel.Set0();
    }
}

void FrogAutomatonStopState::Leave()
{
    FrogAutomatonState::Leave();
    frog->dir.CopyFrom(frog->jumpDirection);
}
