#ifndef WANDERBATMATONSTATE_H
#define WANDERBATMATONSTATE_H

#include "../BatBot.h"

#define WANDER_SPEED 2.0
#define TOTAL_FLOP_TIME 0.5


class WanderBatMatonState : public BatBot::BatAutomatonState
{
    public:
        WanderBatMatonState(BatBot* bat);
        mjObject* player;
        mjVector3 bobVector;
        float goingUpTime = TOTAL_FLOP_TIME;
        float goingDownTime = -1;
        float twistDirFactor = 1;
        virtual void Enter() override;
        virtual void Execute(double t_elapsed) override;
        virtual void Reset() override;
        virtual void Leave() override;
    protected:
    private:
};

#endif // WANDERBATMATONSTATE_H
