#ifndef MJSCENE_H
#define MJSCENE_H

#include <vector>
#include "../core/mjObject.h"
#include "../core/mjGameState.h"
#include "../graphics/mjShader.h"
#include "../util/mjResourceManager.h"
#include "../internalMessaging/mjInternalMessenger.h"

#include "../physics/mjPhysics.h"
#include "../graphics/mjSceneGraph.h"
#include "../graphics/mjCamera.h"
#include "../graphics/mjSkybox.h"
#include "../input/mjInputEvent.h"

namespace mjEngine{

enum mjUniverseState { MJ_UNIVERSE_DEACTIVATED, MJ_UNIVERSE_ACTIVATED };

class mjUniverse
{
    public:
        mjPhysics physics;
        mjSceneGraph sceneGraph;
        mjCamera* camera;
        mjSkybox* skybox = NULL;

        mjResourceManager* resourceManager;

        char* universeName = NULL;

        char* nextUniverseByName = NULL;
        char* transitionByName = NULL;

        std::vector<mjShader*> shaderList;
        float lookAtMatrix[16];
        float projectionMatrix[16];

        mjUniverseState universeState = MJ_UNIVERSE_DEACTIVATED;

        mjUniverse(mjResourceManager* resourceManager);

        virtual void OnActivate(mjGameState* currentGameState);
        virtual void Update(double t_elapsed);
        virtual void OnInput(mjInputEvent& event);
        virtual void Draw(bool clearFrameBuffer = true);
        virtual void OnDeactivate();

        void SetName(const char* thisUniverseName);
        void SetNextUniverse(const char* name);
        void SetTransition(const char* name);

        ~mjUniverse();

protected:
    private:
};

}
#endif // MJSCENE_H
