#include "mjSceneGraph.h"

namespace mjEngine
{
void mjSceneGraph::Update(float t_elapsed)
{
    // This is supposed to optimise drawing by culling objects that are visible. Perhaps also update the
    // models' animations.

}
void mjSceneGraph::Draw(mjCamera* camera, std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix)
{
	unsigned numObjects = drawableObjects.size();
	for (unsigned i= 0 ; i < numObjects; i++)
	{
		drawableObjects[i]->Draw(shaderList, lookAtMatrix, projectionMatrix);
	}



	// The translucent objects should be sorted depending the distance to the camera, and then drawn in z-order

	numObjects = translucentObjects.size();

	if (sortTranslucentObjects)
	{
        for (unsigned i= 0 ; i < numObjects; i++)
        {
            translucentObjects[i]->distSqToCamera = camera->pos.DistanceSquaredTo(translucentObjects[i]->pos);
        }
        std::sort(translucentObjects.begin(), translucentObjects.end(), SortByInvDistanceToCamera);
	}

	for (unsigned i= 0 ; i < numObjects; i++)
		translucentObjects[i]->Draw(shaderList, lookAtMatrix, projectionMatrix);
	}


bool mjSceneGraph::SortByInvDistanceToCamera(mjObject* obj0,mjObject* obj1)
{
    return (obj0->distSqToCamera > obj1->distSqToCamera);
}

}
