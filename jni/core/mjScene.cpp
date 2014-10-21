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
