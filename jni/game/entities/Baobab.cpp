#include "Baobab.h"

Baobab::Baobab(Level* levelData, mjResourceManager* resourceManager)
    : KosmoObject(MJ_AABB, resourceManager, levelData)
{
    this->canCollide = false;



    model = new mjAssimpModel(resourceManager);
    model->LoadFromFile("/common/svn/vasilisa/other/modelSources/meshes/baobab.blend");

    ((mjAABB*)boundingStructure)->isImmovable = true;


}


void Baobab::ProcessPhysicsEffects(float t_elapsed)
{
    // Nothing. The Plant does not respond to effects for now.
}
