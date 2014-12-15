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
	if (t_elapsed < 0.1)
	{
		physics.Update(t_elapsed);
		sceneGraph.Update(t_elapsed);
	} else
	{
		LOGI("Scene: *cough* %3.3f", t_elapsed);
	}
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

mjScene::~mjScene()
{
    //dtor
}
}
