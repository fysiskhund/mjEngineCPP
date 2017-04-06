
#include "KosmoObject.h"


KosmoObject::KosmoObject(structuretype collisionStructureType, mjResourceManager* resourceManager, Level* levelData):
    mjObject(resourceManager, collisionStructureType)
{
 this->levelData = levelData;
}

KosmoObject::KosmoObject(mjResourceManager* resourceManager, Level* levelData):
    mjObject(resourceManager)
{
    this->levelData = levelData;
 //mjObject takes care of the construction
}

void KosmoObject::Update(float t_elapsed)
{
    if (teleportCooldown > 0 )
    {
        teleportCooldown -= t_elapsed;
    }
}
