#ifndef FROGAUTOMATONSTOPSTATE_H
#define FROGAUTOMATONSTOPSTATE_H

#include "../Frog.h"
#include <math.h>

#include <physics/mjCollisionTests.h>



// Frog stops and chooses another direction

class FrogAutomatonStopState: public Frog::FrogAutomatonState
{
    public:
        FrogAutomatonStopState(Frog* frog);
        void Enter() override;
        void Execute(float t_elapsed) override;
        void Leave() override;
    protected:
    private:
};

#endif // FROGAUTOMATONSTOPSTATE_H
