#include "FrogAutomatonStopState.h"

FrogAutomatonStopState::FrogAutomatonStopState(Frog* frog):
Frog::FrogAutomatonState::FrogAutomatonState(frog)
{


}

void FrogAutomatonStopState::Enter()
{
    float theta = ((float)rand() / (float) RAND_MAX)*2.0*3.141592;

    frog->jumpDirection.Set(sin(theta), 0, cos(theta));
    maxTime = 3.0*((float)rand() / (float) RAND_MAX) + 0.5;
}
