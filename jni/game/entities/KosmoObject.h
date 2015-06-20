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
    float teleportCooldown = 0;

    KosmoObject(structuretype collisionStructureType, mjResourceManager* resourceManager, Level* levelData);
    KosmoObject(mjResourceManager* resourceManager, Level* levelData);
    void Update(float t_elapsed) override;
};


#endif // KOSMOOBJECT_H

