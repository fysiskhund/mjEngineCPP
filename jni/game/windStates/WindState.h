#ifndef WINDSTATE_H
#define WINDSTATE_H


#include <stdlib.h>
#include <time.h>

#include "../../ai/mjAutomatonState.h"
#include "../../core/mjVector3.h"

#define RANDOM_F ((float)rand()/(float)RAND_MAX)

using namespace mjEngine;


class WindState : public mjAutomatonState
{
    public:
        mjVector3* wind;
        int stateCount = 0;
        WindState(mjVector3* wind);

        void Enter() override;
        void Leave() override;



    protected:

    private:
};

#endif // WINDSTATE_H
