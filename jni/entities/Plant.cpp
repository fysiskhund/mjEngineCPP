#include "Plant.h"

Plant::Plant(Level* levelData, mjResourceManager& resourceManager)
:mjObject(MJ_AABB)
{
    this->levelData = levelData;
    this->canCollide = false;



	std::string path = "/sdcard/mjEngineCPP/plant.mesh.xml";
    model = resourceManager.FetchModel(path);

	((mjAABB*)boundingStructure)->isImmovable = true;

	path = "/sdcard/mjEngineCPP/leaf.png";
	GLuint glTexture = resourceManager.FetchTexture(path);//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
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
