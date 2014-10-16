#include "Grass.h"

Grass::Grass(Level* levelData)
{
    this->levelData = levelData;


    mjImageLoader imgLoader;
	GLuint glTexture;

	model = new mjModel();
	model->LoadFromFile("/sdcard/mjEngineCPP/grass0.mesh.xml");
	((mjAABB*)boundingStructure)->isImmovable = true;

	glTexture = imgLoader.LoadToGLAndFreeMemory("/sdcard/mjEngineCPP/grassTexture0.png");//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}

}

Grass::~Grass()
{
    //dtor
}
