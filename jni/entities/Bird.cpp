//
//  Bird.cpp
//  mjEngineCPP
//
//  Created by Alejandro Valenzuela Roca on 27/09/14.
//  Copyright (c) 2014 Phong-shaded hallucinations. All rights reserved.
//

#include "Bird.h"
Bird::Bird()
: mjObject(MJ_AABB)
{
	mjImageLoader imgLoader;
	GLuint glTexture;

	model = new mjModel();
	model->LoadFromFile("/sdcard/mjEngineCPP/bird.mesh.xml");
	((mjAABB*)boundingStructure)->isImmovable = true;

	glTexture = imgLoader.LoadToGLAndFreeMemory("/sdcard/mjEngineCPP/birdtexture.png");//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
	for (int i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}
}
