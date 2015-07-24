#ifndef KOSMOOBJECT_H
#define KOSMOOBJECT_H

#include <core/mjObject.h>

#include "../Level.h"

using namespace mjEngine;

class KosmoObject : public mjObject
{
public:

    mjVector3 startPosition;

    bool canGoThroughDoors = false;
    Level* levelData;
    float teleportCooldown = 0;

    KosmoObject(structuretype collisionStructureType, mjResourceManager* resourceManager, Level* levelData);
    KosmoObject(mjResourceManager* resourceManager, Level* levelData);
    void Update(float t_elapsed) override;
    virtual void StartTransitionForTravel(){}
    virtual void EndTransitionForTravel(){}
};


#endif // KOSMOOBJECT_H

