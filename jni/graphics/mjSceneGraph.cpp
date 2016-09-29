#include "mjSceneGraph.h"

namespace mjEngine
{

void mjSceneGraph::Initialize(mjResourceManager* resourceManager)
{
    renderer.Initialize(resourceManager);
}

void mjSceneGraph::Update(float t_elapsed)
{
    // This is supposed to optimise drawing by culling objects that are visible. Perhaps also update the
    // models' animations.

}
void mjSceneGraph::Draw(mjCamera* camera, std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix)
{
    float modelMatrix[16];

    matrixStack.PopAll();
    Matrix4::SetIdentityM(matrixStack.current, 0);

    unsigned numObjects = drawableObjects.size();
	for (unsigned i= 0 ; i < numObjects; i++)
	{
        mjObject* drawableObj = drawableObjects[i];

        if (drawableObj->model->rendererData == NULL)
        {
            renderer.PrepareModel(* drawableObj->model);
        }

        drawableObj->CopyModelMatrixTo(modelMatrix);

                                //mjModel& model, float* modelMatrix, float* lookAtMatrix, float* projectionMatrix, mjModelPose* pose, mjMatrixStack* stack)
        renderer.RenderModel(* drawableObj->model, modelMatrix, lookAtMatrix, projectionMatrix, NULL, &matrixStack,
                             drawableObj->customShaders, drawableObj->customTextures);

        //drawableObjects[i]->Draw(shaderList, lookAtMatrix, projectionMatrix, &matrixStack);
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
    {
        //FIXME!!
        //translucentObjects[i]->Draw(shaderList, lookAtMatrix, projectionMatrix, &matrixStack);
    }

}
void mjSceneGraph::CleanUp()
{
    drawableObjects.clear();
    translucentObjects.clear();
    shadowCasters.clear();
}

mjSceneGraph::~mjSceneGraph()
{

    CleanUp();
}


bool mjSceneGraph::SortByInvDistanceToCamera(mjObject* obj0,mjObject* obj1)
{
    return (obj0->distSqToCamera > obj1->distSqToCamera);
}

}
