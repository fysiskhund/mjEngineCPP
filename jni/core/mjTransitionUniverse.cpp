#include "mjTransitionUniverse.h"

namespace mjEngine {


mjTransitionUniverse::mjTransitionUniverse(mjResourceManager* resourceManager)
 : mjUniverse(resourceManager)
{

}

void mjTransitionUniverse::OnActivate(mjGameState* currentGameState)
{
    transitionPercentage = 0;
    transitionElapsedTime = 0;
    lastLoop = false;
}

void mjTransitionUniverse::OnDeactivate()
{
    // Deactivate the fromUniverse when moving away from the transition
    fromUniverse->OnDeactivate();
}

void mjTransitionUniverse::Update(double t_elapsed)
{
    transitionElapsedTime += t_elapsed;
    transitionPercentage = transitionElapsedTime/transitionDuration;

    if (transitionDuration <= transitionElapsedTime)
    {
        if (!lastLoop)
        {
            transitionElapsedTime = transitionDuration;
            transitionPercentage = 1.0f;
            lastLoop = true;
        } else
        {
            SetNextUniverse(toUniverse->universeName);
        }
    }
}



}
