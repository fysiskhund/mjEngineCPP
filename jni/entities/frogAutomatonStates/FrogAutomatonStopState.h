#ifndef FROGAUTOMATONSTOPSTATE_H
#define FROGAUTOMATONSTOPSTATE_H

#include "../Frog.h"
#include <math.h>


// Frog stops and chooses another direction

class FrogAutomatonStopState: Frog::FrogAutomatonState
{
    public:
        Frog* frog;
        FrogAutomatonStopState(Frog* frog);
        void Enter() override;
    protected:
    private:
};

#endif // FROGAUTOMATONSTOPSTATE_H
