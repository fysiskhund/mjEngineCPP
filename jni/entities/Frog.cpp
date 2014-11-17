#include "Frog.h"

Frog::Frog(Level* levelData, mjResourceManager& resourceManager):
mjObject(MJ_AABB)
{
    this->levelData = levelData;
    model = resourceManager.FetchModel("frog.mesh.xml");
    glTexture = resourceManager.FetchTexture("frog.png");

}
