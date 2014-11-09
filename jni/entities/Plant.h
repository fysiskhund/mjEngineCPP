#ifndef PLANT_H
#define PLANT_H

#include "../core/mjObject.h"
#include "../ai/mjAutomaton.h"
#include "../util/mjResourceManager.h"

#include "../game/Level.h"


using namespace mjEngine;

class Plant : public mjObject, public mjAutomaton
{
    public:
        Plant(Level* levelData, mjResourceManager& resourceManager);
        //BatBot(const BatBot& other);
        Level* levelData;
        ~Plant();
        virtual void ProcessPhysicsEffects(float t_elapsed) override;
    protected:
    private:
};

#endif // PLANT_H
