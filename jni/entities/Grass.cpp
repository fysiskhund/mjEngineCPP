#include "Grass.h"

Grass::Grass(Level* levelData)
:mjObject(MJ_AABB)
{
    this->levelData = levelData;
    this->canCollide = false;

    mjImageLoader imgLoader;
	GLuint glTexture;

	model = new mjModel();
	model->LoadFromFile("/sdcard/mjEngineCPP/grass.mesh.xml");
	((mjAABB*)boundingStructure)->isImmovable = true;

	glTexture = imgLoader.LoadToGLAndFreeMemory("/sdcard/mjEngineCPP/grass0.png");//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}

}

void Grass::ProcessPhysicsEffects(float t_elapsed)
{
    // Nothing. The grass does not respond to effects for now.
}

Grass::~Grass()
{
    //dtor
}
