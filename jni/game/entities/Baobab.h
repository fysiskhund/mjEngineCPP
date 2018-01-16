#ifndef BAOBAB_H
#define BAOBAB_H


#include <core/mjObject.h>
#include <ai/mjAutomaton.h>
#include <util/mjResourceManager.h>
#include <graphics/mjAssimpModel.h>


#include "../Level.h"


#include "KosmoObject.h"

class Baobab: public KosmoObject
{
public:
    Baobab(Level* levelData, mjResourceManager* resourceManager);
    void ProcessPhysicsEffects(double t_elapsed);
};

#endif // BAOBAB_H
