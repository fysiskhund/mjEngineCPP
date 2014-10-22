#include "PlatformUniverseScene.h"

PlatformUniverseScene::PlatformUniverseScene()
{
    //ctor
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

	char wanderingCloudName[1024];
	/*for (int i = 0; i < 3; i++)
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
