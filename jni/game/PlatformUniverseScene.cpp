#include "PlatformUniverseScene.h"

PlatformUniverseScene::PlatformUniverseScene(mjResourceManager* resourceManager)
:mjScene(resourceManager)
{

    entityCreator = new EntityCreator(resourceManager);
    srand(time(0));

    levelFilename  = "levels/testLevel.xml";
    resourceManager->PrependFullFilePath(levelFilename);
}


void PlatformUniverseScene::Initialise(int width, int height)
{
    InitShaders();
    camera = new mj3rdPersonCamera();
    level = new Level(resourceManager);
    //LOGI("Fetching sound %s", "music/fyra.ogg");
    musicPlayer.Load(resourceManager->FetchSound("music/fyra.ogg"), 0);
    musicPlayer.Play();
    // Some adjustments
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);



    glViewport(0, 0, width, height);
    //checkGlError("glViewport");
    mjVector3 o;





    level->LoadFromFile(levelFilename.c_str());
    ambient.InitGlowBeings(level, camera, &physics, &shaderList, &sceneGraph, *resourceManager);
    //ambient.CreateDustDevil(o, 12, 10);
    entityCreator->PopulateLevel(&level->doc, level);


    character = (Character*) level->GetEntityByID("character0");
    LOGI("character is at %p", character);

    character->gravity = &physics.gravity;

    LOGI("Here2");
    character->modelOffset.Set(0,-0.825,0);


    mjVector3 cameraOffset;
    cameraOffset.Set(0,0.7,0);
    //LOGI("Here3");

    mjObject* batBot0 = level->GetEntityByID("bat.002");

    //camera->SetTarget(&batBot0->pos, cameraOffset);
    camera->SetTarget(&character->pos, cameraOffset);
    camera->r = 3;
    camera->SetAsCurrentCamera();

    //charBoundStruct->SetCorners()
    //((mjSphere*) character.boundingStructure)->r = 0.5;




    float closeUpFactor = 0.5;
    ratio = closeUpFactor*((float)width)/((float)height);
    Matrix4::FrustumM(projectionMatrix, 0,
            				   -ratio, ratio, -closeUpFactor, closeUpFactor, 0.5, 70);


    //LOGI("setupSkybox");
    SetUpSkybox();
    skybox->TieShaders(shaderList);


    LOGI("Adding entities");
    for (unsigned i = 0; i < level->entities.size(); i++)
    {
        level->entities[i]->TieShaders(shaderList);
        sceneGraph.drawableObjects.push_back(level->entities[i]);
        physics.AddObject(level->entities[i], 0);
    }
    LOGI("Now adding terrain");
    for (unsigned i = 0; i < level->terrain.size(); i++)
    {
        level->terrain[i]->TieShaders(shaderList);
        sceneGraph.drawableObjects.push_back(level->terrain[i]);
        physics.AddObject(level->terrain[i], 1);
    }

    LOGI("End of init");
    //checkGlError("end of init");
}

void PlatformUniverseScene::InitShaders()
{
	mjDefaultShaders* defaultShaders = new mjDefaultShaders();
	mjSkyboxShaders* skyboxShaders = new mjSkyboxShaders();

	shaderList.push_back(defaultShaders);
	shaderList.push_back(skyboxShaders);
}
void PlatformUniverseScene::SetUpSkybox()
{
	skybox = new mjSkybox(resourceManager);

	mjImageLoader imgLoader;
	mjModel* skyboxBox;

	skyboxBox = resourceManager->FetchModel("skybox.mesh.xml");

	mjModel* skyboxPlane;
	skyboxPlane= resourceManager->FetchModel("skybox_plane.mesh.xml");

	skybox->SetModels(skyboxBox, skyboxPlane);

	skybox->LoadTexturesFromPrefix("bluesky/skybox");

	/*char wanderingCloudName[1024];
	for (unsigned i = 0; i < 3; i++)
	{
		snprintf(wanderingCloudName, 1024, "%s%d%s",  "/sdcard/mjEngineCPP/bluesky/wandering_cloud", i, ".png");
		GLuint tex0 = imgLoader.LoadToGLAndFreeMemory(wanderingCloudName);
		skybox->PushLevel(new mjSkyboxLevelData(tex0, i, 0, 0.01*i+0.02, 0));
	}*/




	skybox->SetCameraPos(&camera->pos);

	LOGI("after SetCamerapos");
}
void PlatformUniverseScene::Update(float t_elapsed)
{
	if (t_elapsed < 0.1)
	{
		// Update phase
		if (character->pos.y < -5)
		{
			character->pos.CopyFrom(character->startPosition);
			character->vel.Set0();
            character->teleportCooldown = 1;
		}
		ambient.Update(t_elapsed);
		mjPhysicsEffect* windEffect = new mjPhysicsEffect();
		windEffect->type = MJ_FORCE;
		windEffect->action = MJ_ADD_FORCE;
		windEffect->value.CopyFrom(ambient.wind);

		//LOGI("ambient.wind %p, windEffect %3.3f %3.3f %3.3f\n", &ambient.wind, windEffect->value.x, windEffect->value.y, windEffect->value.z);
		physics.globalEffects.push_back(windEffect);
		physics.Update(t_elapsed);
		camera->Update(t_elapsed);
		skybox->Update(t_elapsed);
		if (cameraAnglesModifier.GetNorm() > 0.2) {
			camera->theta += -0.02*cameraAnglesModifier.y;
			if (camera->theta > 6.283184)
				camera->theta -= 6.283184;
			else if (camera->theta < 0)
				camera->theta = 6.283184 + camera->theta;

			camera->phi += -0.02*cameraAnglesModifier.x;

			if (camera->phi > 6.283184)
				camera->phi -= 6.283184;
			else if (camera->phi < 0)
				camera->phi = 6.283184 + camera->phi;

		} else
		{
			cameraAnglesModifier.Set0();
		}
	} else {
		LOGI("Scene: Cough %3.3f", t_elapsed);
	}

}
void PlatformUniverseScene::Draw()
{
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    skybox->Draw(shaderList, lookAtMatrix, projectionMatrix);
    camera->GetLookAtMatrix(lookAtMatrix);
    sceneGraph.Draw(camera, shaderList, lookAtMatrix, projectionMatrix);


}
