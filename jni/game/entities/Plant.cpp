#include "Plant.h"

Plant::Plant(Level* levelData, mjResourceManager* resourceManager)
: KosmoObject(MJ_AABB, resourceManager, levelData)
{
    this->canCollide = false;



    model = resourceManager->FetchModel("entities/plant/plant.mesh.xml");

	((mjAABB*)boundingStructure)->isImmovable = true;

    GLuint glTexture = resourceManager->FetchTexture("entities/plant/leaf.png", GL_REPEAT);//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}

}

void Plant::ProcessPhysicsEffects(float t_elapsed)
{
    // Nothing. The Plant does not respond to effects for now.
}

Plant::~Plant()
{
    //dtor
}
