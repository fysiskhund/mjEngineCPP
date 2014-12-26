#ifndef MJSCENEMANAGER_H
#define MJSCENEMANAGER_H

#include <vector>
#include "mjScene.h"


namespace mjEngine{



class mjSceneManager
{
    public:
        std::vector<mjScene*> scenes;
        mjScene* currentScene = NULL;

        mjSceneManager();
        void SetFirstScene(mjScene* firstScene);

        void Update(float t_elapsed);
    protected:
    private:
};

}
#endif // MJSCENEMANAGER_H
