
#include "KosmoObject.h"


KosmoObject::KosmoObject(structuretype collisionStructureType, mjResourceManager* resourceManager, Level* levelData):
    mjObject(collisionStructureType, resourceManager)
{
 this->levelData = levelData;
}

KosmoObject::KosmoObject(mjResourceManager* resourceManager, Level* levelData):
    mjObject(resourceManager)
{
    this->levelData = levelData;
 //mjObject takes care of the construction
}
