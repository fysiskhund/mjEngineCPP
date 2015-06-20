#ifndef KOSMOOBJECT_H
#define KOSMOOBJECT_H

#include <core/mjObject.h>

#include "../Level.h"

using namespace mjEngine;

class KosmoObject : public mjObject
{
public:
    bool canGoThroughDoors = false;
    Level* levelData;

    KosmoObject(structuretype collisionStructureType, mjResourceManager* resourceManager, Level* levelData);
    KosmoObject(mjResourceManager* resourceManager, Level* levelData);
};


#endif // KOSMOOBJECT_H

