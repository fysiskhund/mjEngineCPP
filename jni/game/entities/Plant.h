#ifndef PLANT_H
#define PLANT_H

#include <core/mjObject.h>
#include <ai/mjAutomaton.h>
#include <util/mjResourceManager.h>

#include "../Level.h"

#include "KosmoObject.h"


using namespace mjEngine;

class Plant : public KosmoObject, public mjAutomaton
{
    public:
        Plant(Level* levelData, mjResourceManager* resourceManager);
        //BatBot(const BatBot& other);
        ~Plant();
        virtual void ProcessPhysicsEffects(float t_elapsed) override;
    protected:
    private:
};

#endif // PLANT_H
