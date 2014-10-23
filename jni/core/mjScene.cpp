#include "mjScene.h"

namespace mjEngine
{

mjScene::mjScene()
{
    //ctor
}

void mjScene::OnActivate()
{

}


void mjScene::Update(float t_elapsed)
{
    physics.Update(t_elapsed);
    sceneGraph.Update(t_elapsed);
}

void mjScene::Draw()
{
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    camera->GetLookAtMatrix(lookAtMatrix);
    sceneGraph.Draw(shaderList, lookAtMatrix, projectionMatrix);
}

void mjScene::OnDeactivate()
{

}

mjScene::~mjScene()
{
    //dtor
}
}
