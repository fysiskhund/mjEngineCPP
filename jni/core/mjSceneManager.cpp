#include "mjSceneManager.h"

namespace mjEngine{

mjSceneManager::mjSceneManager()
{
    //ctor
}
void mjSceneManager::SetFirstScene(mjScene* firstScene)
{
	currentScene = firstScene;
	currentScene->OnActivate();
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
	if (currentScene->nextSceneByName)
	{
        mjScene* nextScene = NULL;
        // Look up next scene
        for (unsigned i = 0; i < scenes.size(); i++)
        {
            if (strncmp(currentScene->nextSceneByName, scenes[i]->sceneName, 128))
            {
                nextScene = scenes[i];
            }
        }
        if (nextScene)
        {
            delete [] currentScene->nextSceneByName;
            currentScene->nextSceneByName = NULL; // Remove the "switch scene" indicator
            currentScene->OnDeactivate();
            currentScene = nextScene;
            currentScene->OnActivate();
        }

	}
}
}
