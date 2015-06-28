#ifndef FROGBOSSAUTOMATONHUNTSTATE_H
#define FROGBOSSAUTOMATONHUNTSTATE_H

#include "../FrogBoss.h"
#include <math.h>

#include <physics/mjCollisionTests.h>



// Upon finding character0, FrogBoss prepares for SLAM!!!!!!!!!

class FrogBossAutomatonHuntState: public FrogBoss::FrogBossAutomatonState
{
    public:
        FrogBossAutomatonHuntState(FrogBoss* frogBoss);
        void Enter() override;
        void Execute(float t_elapsed) override;
        void Leave() override;
    protected:
    private:
};

#endif // FROGBOSSAUTOMATONHUNTSTATE_H
