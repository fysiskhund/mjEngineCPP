#include "Baobab.h"

Baobab::Baobab(Level* levelData, mjResourceManager* resourceManager)
    : KosmoObject(MJ_AABB, resourceManager, levelData)
{
    this->canCollide = false;



    model = resourceManager->FetchModel("plant.mesh.xml");

    ((mjAABB*)boundingStructure)->isImmovable = true;

    GLuint glTexture = resourceManager->FetchTexture("leafR.png", GL_REPEAT);//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
    for (unsigned i = 0; i < model->meshes.size(); i++)
    {
        model->meshes[i]->glTexture = glTexture;
    }
}


void Baobab::ProcessPhysicsEffects(float t_elapsed)
{
    // Nothing. The Plant does not respond to effects for now.
}
