#ifndef AMBIENT_H
#define AMBIENT_H

#include <stdlib.h>
#include <time.h>

#include "../ai/mjAutomaton.h"
#include "../ai/mjAutomatonState.h"
#include "windStates/SteadyDirectionState.h"
#include "windStates/DustDevilState.h"


using namespace mjEngine;

class Ambient
{
    public:

        mjVector3 wind;

        Ambient();

        void Update(float t_elapsed);

        mjAutomaton windAutomaton;
    protected:
    private:
};

#endif // AMBIENT_H
