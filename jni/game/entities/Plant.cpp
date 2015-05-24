#include "Plant.h"

Plant::Plant(Level* levelData, mjResourceManager* resourceManager)
: mjObject(MJ_AABB, resourceManager)
{
    this->levelData = levelData;
    this->canCollide = false;



    model = resourceManager->FetchModel("plant.mesh.xml");

	((mjAABB*)boundingStructure)->isImmovable = true;

	GLuint glTexture = resourceManager->FetchTexture("leaf.png", GL_REPEAT);//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
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
