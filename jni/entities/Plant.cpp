#include "Plant.h"

Plant::Plant(Level* levelData)
:mjObject(MJ_AABB)
{
    this->levelData = levelData;
    this->canCollide = false;

    mjImageLoader imgLoader;
	GLuint glTexture;

	model = new mjModel();
	model->LoadFromFile("/sdcard/mjEngineCPP/plant.mesh.xml");
	((mjAABB*)boundingStructure)->isImmovable = true;

	glTexture = imgLoader.LoadToGLAndFreeMemory("/sdcard/mjEngineCPP/leaf.png");//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
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
