#include "mjSceneGraph.h"

namespace mjEngine
{
void mjSceneGraph::Update(float t_elapsed)
{
    // This is supposed to optimise drawing by culling objects that are visible. Perhaps also update the
    // models' animations.

}
void mjSceneGraph::Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix)
{
	int numObjects = drawableObjects.size();
	for (int i= 0 ; i < numObjects; i++)
	{
		drawableObjects[i]->Draw(shaderList, lookAtMatrix, projectionMatrix);
	}
}
}
