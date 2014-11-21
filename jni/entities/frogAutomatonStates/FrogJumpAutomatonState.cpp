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

    maxTime = 1; // Jump each 3 secnds
    //FIXME: change to detect frog has footing
}

void FrogAutomatonJumpState::Execute(float t_elapsed)
{
    if (frog->pos.y < -3)
    {
        frog->pos.CopyFrom(frog->startPosition);
        frog->vel.Set0();
    }

}
