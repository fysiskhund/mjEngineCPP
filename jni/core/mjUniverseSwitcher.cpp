#include "mjUniverseSwitcher.h"

namespace mjEngine{

mjUniverseSwitcher::mjUniverseSwitcher()
{
    //ctor
}
void mjUniverseSwitcher::SetFirstUniverse(mjUniverse* firstUniverse, mjGameState* currentGameState)
{
    this->currentGameState = currentGameState;
    currentUniverse = firstUniverse;
    currentUniverse->OnActivate(currentGameState);
}
void mjUniverseSwitcher::Update(double t_elapsed)
{
	if (t_elapsed < 0.1)
	{
        currentUniverse->Update(t_elapsed);
        currentUniverse->Draw();
	} else
	{
		LOGI("Hiccup: t_elapsed is too big (%3.3f)", t_elapsed);
	}

    if (currentUniverse->nextUniverseByName)
	{
        mjUniverse* nextUniverse = NULL;


            // Look up next scene
            for (unsigned i = 0; i < universes.size(); i++)
            {
                //LOGI("Searching for %s =? %s", currentScene->nextSceneByName, scenes[i]->sceneName);
                if (strncmp(currentUniverse->nextUniverseByName, universes[i]->universeName, 128) == 0)
                {
                    LOGI("Switching to %s!", universes[i]->universeName);
                    nextUniverse = universes[i];
                    break;
                }
            }

        if (currentUniverse->transitionByName){
             // Look up transition, set the fromUniverse and toUniverse and use that as next scene
            mjTransitionUniverse* transition = NULL;
            for (unsigned i = 0; i < universes.size(); i++)
            {
                if (strncmp(currentUniverse->transitionByName, universes[i]->universeName, 128) == 0)
                {
                    LOGI("transitionUniverse %s found!", universes[i]->universeName);
                    transition = (mjTransitionUniverse* ) universes[i];
                    break;
                }
            }
            transition->fromUniverse = currentUniverse;
            transition->toUniverse = nextUniverse;



            if (nextUniverse->universeState == MJ_UNIVERSE_DEACTIVATED)
            {
                nextUniverse->OnActivate(currentGameState);
            }

            // Remove the "switch scene" indicator
            delete [] currentUniverse->nextUniverseByName;
            currentUniverse->nextUniverseByName = NULL;

            transition->OnActivate(currentGameState);

            currentUniverse = transition;

        } else
        {
            if (nextUniverse)
            {
                delete [] currentUniverse->nextUniverseByName;
                currentUniverse->nextUniverseByName = NULL; // Remove the "switch scene" indicator
                currentUniverse->OnDeactivate();
                currentUniverse = nextUniverse;
                if (currentUniverse->universeState == MJ_UNIVERSE_DEACTIVATED)
                {
                    currentUniverse->OnActivate(currentGameState);
                }
            } else
            {
                LOGI("Error: Scene %s not found!", currentUniverse->nextUniverseByName);
            }
        }

	}
}
}
