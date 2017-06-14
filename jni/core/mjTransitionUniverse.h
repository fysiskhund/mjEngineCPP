#ifndef MJTRANSITIONUNIVERSE_H
#define MJTRANSITIONUNIVERSE_H

#include "mjUniverse.h"
#include "../util/mjResourceManager.h"

namespace mjEngine {



class mjTransitionUniverse: public mjUniverse
{
public:

    mjUniverse* fromUniverse = NULL;
    mjUniverse* toUniverse = NULL;

    double transitionElapsedTime = 0;
    double transitionPercentage = 0;
    double transitionDuration = 0.3;
    bool lastLoop = false;

    mjTransitionUniverse(mjResourceManager* resourceManager);

    // mjUniverse interface
public:
    void OnActivate(mjGameState* currentGameState) override;
    void OnDeactivate() override;
    void Update(double t_elapsed) override;


};

}
#endif // MJTRANSITIONUNIVERSE_H
