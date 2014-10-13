#ifndef BATBOT_H
#define BATBOT_H

#include <vector>

#include "../core/mjObject.h"
#include "../game/Level.h"
#include "../ai/mjAutomaton.h"
//#include "../ai/mjAutomatonState.h"




using namespace mjEngine;



class BatBot: public mjObject, public mjAutomaton
{
    public:
        BatBot(Level* levelData);
        //BatBot(const BatBot& other);
        Level* levelData;

        float wanderRadiusMin = 3;
        float wanderRadiusMax = 10;
        mjVector3 wanderDir;

        bool ignoresGravity = true;

        virtual void Update(float t_elapsed) override;

        virtual void ProcessPhysicsEffects(float t_elapsed) override;


        class BatAutomatonState: public mjAutomatonState
        {
        public:
            BatAutomatonState(BatBot* bat);
            BatBot* bat;
        };


    protected:
    private:
};





#endif // BATBOT_H
