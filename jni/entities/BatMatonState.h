#ifndef BATMATONSTATE_H
#define BATMATONSTATE_H

#include "../ai/mjAutomatonState.h"
#include "../game/Level.h"
//#include "BatBot.h"

using namespace mjEngine;

class BatMatonState : public mjAutomatonState
{
    public:
        BatMatonState(Level* levelData);//, BatBot* batbot);
        ~BatMatonState();
        Level* levelData;
    protected:
    private:
};

#endif // BATMATONSTATE_H
