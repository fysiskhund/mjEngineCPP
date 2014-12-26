#include "mjSceneManager.h"

namespace mjEngine{

mjSceneManager::mjSceneManager()
{
    //ctor
}
void mjSceneManager::SetFirstScene(mjScene* firstScene)
{
	currentScene = firstScene;
}
void mjSceneManager::Update(float t_elapsed)
{
	if (t_elapsed < 0.1)
	{
		currentScene->Update(t_elapsed);
		currentScene->Draw();
	} else
	{
		LOGI("Hiccup: t_elapsed is too big (%3.3f)", t_elapsed);
	}
}
}
