//
//  Bird.cpp
//  mjEngineCPP
//
//  Created by Alejandro Valenzuela Roca on 27/09/14.
//  Copyright (c) 2014 Phong-shaded hallucinations. All rights reserved.
//

#include "Bird.h"
Bird::Bird(Level* levelData, mjResourceManager* resourceManager)
: KosmoObject(MJ_AABB, resourceManager, levelData)
{

	GLuint glTexture;

    model = resourceManager->FetchModel("entities/bird/bird.mesh.xml");




	((mjAABB*)boundingStructure)->isImmovable = true;

    glTexture = resourceManager->FetchTexture("entities/bird/birdtexture.png", GL_REPEAT);//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}
}
