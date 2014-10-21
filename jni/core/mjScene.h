#ifndef MJSCENE_H
#define MJSCENE_H

#include <vector>
#include "../core/mjObject.h"
#include "../graphics/mjShader.h"

#include "../physics/mjPhysics.h"
#include "../graphics/mjSceneGraph.h"

namespace mjEngine{

class mjScene
{
    public:
        mjPhysics physics;
        mjSceneGraph sceneGraph;

        char* sceneName;

        char* nextSceneByName = NULL;

        std::vector<mjShader*> shaderList;
        float* lookAtMatrix;
        float* projectionMatrix;


        mjScene();

        virtual void OnActivate();
        virtual void Update(float t_elapsed);
        virtual void Draw();
        virtual void OnDeactivate();

        ~mjScene();
    protected:
    private:
};

}
#endif // MJSCENE_H
