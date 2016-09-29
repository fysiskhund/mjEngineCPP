#ifndef MJSCENE_H
#define MJSCENE_H

#include <vector>
#include "../core/mjObject.h"
#include "../graphics/mjShader.h"
#include "../util/mjResourceManager.h"

#include "../physics/mjPhysics.h"
#include "../graphics/mjSceneGraph.h"
#include "../graphics/mjCamera.h"
#include "../graphics/mjSkybox.h"
#include "../input/mjInputEvent.h"

namespace mjEngine{

class mjScene
{
    public:
        mjPhysics physics;
        mjSceneGraph sceneGraph;
        mjCamera* camera;
        mjSkybox* skybox = NULL;

        mjResourceManager* resourceManager;

        const char* sceneName = "";

        char* nextSceneByName = NULL;

        std::vector<mjShader*> shaderList;
        float lookAtMatrix[16];
        float projectionMatrix[16];


        mjScene(mjResourceManager* resourceManager);

        virtual void OnActivate();
        virtual void Update(float t_elapsed);
        virtual void OnInput(mjInputEvent& event);
        virtual void Draw();
        virtual void OnDeactivate();

        void SetNextScene(const char* name);

        ~mjScene();
    protected:
    private:
};

}
#endif // MJSCENE_H
