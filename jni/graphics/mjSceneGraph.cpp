#include "mjSceneGraph.h"

namespace mjEngine
{
void mjSceneGraph::Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix)
{
	int numObjects = drawableObjects.size();
	for (int i= 0 ; i < numObjects; i++)
	{
		drawableObjects[i]->Draw(shaderList, lookAtMatrix, projectionMatrix);
	}
}
}
