#ifndef FROGJUMPAUTOMATONSTATE_H
#define FROGJUMPAUTOMATONSTATE_H

#include <physics/mjCollisionTests.h>

#include "../FrogBoss.h"


class FrogBossAutomatonSlamState: public FrogBoss::FrogBossAutomatonState
{
    public:

        mjVector3 trajectory;
        mjVector3 travelToSlamLocation;
        int jumpType = 0; // when == 3, frogBoss will not jump vertically first, but rather will move
                          // makes it easier to defeat
        FrogBossAutomatonSlamState(FrogBoss* frogBoss);
        void Enter() override;
        void Execute(double t_elapsed) override;
    protected:
    private:
};

#endif // FROGJUMPAUTOMATONSTATE_H
