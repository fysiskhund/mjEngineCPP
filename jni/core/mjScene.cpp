#include "mjScene.h"

namespace mjEngine
{

mjScene::mjScene(mjResourceManager* resourceManager)
{
    this->resourceManager = resourceManager;
}

void mjScene::OnActivate()
{

}


void mjScene::Update(float t_elapsed)
{
    physics.Update(t_elapsed);
    sceneGraph.Update(t_elapsed);
}

void mjScene::OnInput(mjInputEvent& event)
{

}

void mjScene::Draw()
{
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    camera->GetLookAtMatrix(lookAtMatrix);
    sceneGraph.Draw(camera, shaderList, lookAtMatrix, projectionMatrix);
}

void mjScene::OnDeactivate()
{

}

void mjScene::SetNextScene(const char* name)
{
    if (nextSceneByName)
    {
        delete [] nextSceneByName;
    }
    nextSceneByName = new char[strnlen(name, 128)+1];
    LOGI("%s %d: new %s", __FILE__, __LINE__, "char (scene by name)");
    strncpy(nextSceneByName, name, strnlen(name, 128));
}

mjScene::~mjScene()
{
    //dtor
}
}
