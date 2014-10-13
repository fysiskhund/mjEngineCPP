#ifndef WANDERBATMATONSTATE_H
#define WANDERBATMATONSTATE_H

#include "../BatBot.h"

#define WANDER_SPEED 2.0

class WanderBatMatonState : public BatBot::BatAutomatonState
{
    public:
        WanderBatMatonState(BatBot* bat);
        mjObject* player;
        virtual void Execute(float t_elapsed) override;
    protected:
    private:
};

#endif // WANDERBATMATONSTATE_H
