#ifndef BATBOT_H
#define BATBOT_H

#include <vector>

#include "../core/mjObject.h"
#include "../game/Level.h"
#include "../ai/mjAutomatonState.h"
#include "BatMaton.h"




using namespace mjEngine;




class BatBot: public mjObject, public BatMaton
{
    public:
        BatBot(Level* levelData);
        //BatBot(const BatBot& other);
        Level* levelData;




        class BatAutomatonState: public mjAutomatonState
        {
        public:
            BatAutomatonState(BatBot* bat);
            BatBot* bat;
        };

        std::vector<BatAutomatonState*> states;

    protected:
    private:
};




#endif // BATBOT_H
