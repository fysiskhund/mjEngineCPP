#ifndef FROGBOSSAUTOMATONWAITFORLANDINGSTATE_H
#define FROGBOSSAUTOMATONWAITFORLANDINGSTATE_H

#include "../FrogBoss.h"
#include <math.h>

#include <physics/mjCollisionTests.h>





class FrogBossAutomatonWaitForLandingState: public FrogBoss::FrogBossAutomatonState
{
    public:
        bool maxTimeMustBeReset = false;
        FrogBossAutomatonWaitForLandingState(FrogBoss* frogBoss);
        void Enter() override;
        void Execute(float t_elapsed) override;
        void Leave() override;
    protected:
    private:
};

#endif // FROGBOSSAUTOMATONHUNTSTATE_H
