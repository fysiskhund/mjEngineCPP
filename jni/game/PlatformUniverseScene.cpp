#include "PlatformUniverseScene.h"

PlatformUniverseScene::PlatformUniverseScene()
{
    wind.Set(0,0,0.01);
    srand(time(0));

}

void PlatformUniverseScene::InitGlowBeings()
{
    unsigned total = 100;


    for (unsigned i = 0; i < total; i++)
    {
        GlowBeing* glowBeing = new GlowBeing(camera);







        glowBeing->TieShaders(shaderList);

        physics.AddObject(glowBeing, 0);

        sceneGraph.translucentObjects.push_back(glowBeing);

        glowBeing->Reposition();

        glowBeings.push_back(glowBeing);
    }
}

void PlatformUniverseScene::Initialise(int width, int height)
{
    InitShaders();
    camera = new mj3rdPersonCamera();
    level = new Level();
    // Some adjustments
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);



    glViewport(0, 0, width, height);
    //checkGlError("glViewport");
    InitGlowBeings();

    level->LoadFromFile("/sdcard/mjEngineCPP/levels/testlevel.xml");
    entityCreator.PopulateLevel(&level->doc, level);


    character = (Character*) level->GetEntityByID("character0");
    LOGI("character is at %p", character);

    character->gravity = &physics.gravity;

    LOGI("Here2");
    character->modelOffset.Set(0,-0.825,0);


    mjVector3 cameraOffset;
    cameraOffset.Set(0,0.7,0);
    LOGI("Here3");
    camera->SetTarget(&character->pos, cameraOffset);
    camera->r = 3;

    //charBoundStruct->SetCorners()
    //((mjSphere*) character.boundingStructure)->r = 0.5;




    float closeUpFactor = 0.5;
    ratio = closeUpFactor*((float)width)/((float)height);
    Matrix4::FrustumM(projectionMatrix, 0,
            				   -ratio, ratio, -closeUpFactor, closeUpFactor, 0.5, 50);


    LOGI("setupSkybox");
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
	skybox = new mjSkybox();

	mjImageLoader imgLoader;
	mjModel* skyboxBox = new mjModel();
	skyboxBox->LoadFromFile("/sdcard/mjEngineCPP/skybox.mesh.xml");

	mjModel* skyboxPlane = new mjModel();
	skyboxPlane->LoadFromFile("/sdcard/mjEngineCPP/skybox_plane.mesh.xml");

	skybox->SetModels(skyboxBox, skyboxPlane);

	skybox->LoadTexturesFromPrefix("/sdcard/mjEngineCPP/bluesky/skybox");

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
// Update phase
	if (character->pos.y < -5)
	{
		character->pos.Set0();
		character->pos.y = 10;
		character->vel.y = 0;
	}
    mjPhysicsEffect* windEffect = new mjPhysicsEffect();
    windEffect->type = MJ_FORCE;
    windEffect->action = MJ_ADD_FORCE;
    windEffect->value.CopyFrom(wind);

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

}
void PlatformUniverseScene::Draw()
{
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    skybox->Draw(shaderList, lookAtMatrix, projectionMatrix);
    camera->GetLookAtMatrix(lookAtMatrix);
    sceneGraph.Draw(shaderList, lookAtMatrix, projectionMatrix);


}
