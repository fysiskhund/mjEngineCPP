#include "mjSceneGraph.h"

namespace mjEngine
{

void mjSceneGraph::Initialize(mjResourceManager* resourceManager)
{
    this->resourceManager = resourceManager;
}

/*void mjSceneGraph::AddToDrawable(mjObject* object, bool isDrawable=true, bool castsShadow, bool isTranslucent)
{
    if (isDrawable)
    {
        drawableObjects.push_back(object);
    } else if (isTranslucent)
    {
        translucentObjects.push_back(object);
    }
    if (castsShadow)
    {
        shadowCasters.push_back(object);
    }

    renderer.PrepareModel(object->model);
}*/

void mjSceneGraph::AddGroup(std::vector<mjObject*>* group, bool toDrawable, bool toShadowCasters, bool toTranslucent)
{
    if (toDrawable)
    {
        if (drawableObjects.capacity() < drawableObjects.size()+group->size())
        {
            drawableObjects.reserve(drawableObjects.size()+group->size());
        }
        for (int i = 0; i < group->size(); i++)
        {
            drawableObjects.push_back((*group)[i]);
        }
    }
    if (toShadowCasters)
    {
        if (shadowCasters.capacity() < shadowCasters.size()+group->size())
        {
            shadowCasters.reserve(shadowCasters.size()+group->size());
        }
        for (int i = 0; i < group->size(); i++)
        {
            shadowCasters.push_back((*group)[i]);
        }
    }
    if (toTranslucent)
    {
        if (translucentObjects.capacity() < translucentObjects.size()+group->size())
        {
            translucentObjects.reserve(translucentObjects.size()+group->size());
        }
        for (int i = 0; i < group->size(); i++)
        {
            translucentObjects.push_back((*group)[i]);
        }
    }
}

void mjSceneGraph::RemoveGroup(std::vector<mjObject*>* group)
{
    for (int i = 0; i < group->size(); i++)
    {
        std::vector<mjObject*>::iterator end = drawableObjects.end();
        for (std::vector<mjObject*>::iterator j = drawableObjects.begin(); j != end; j++)
        {
            if ((*group)[i] == *j)
            {
                drawableObjects.erase(j);
                break;
            }
        }
    }
}

void mjSceneGraph::Update(float t_elapsed)
{
    // This is supposed to optimise drawing by culling objects that are visible. Perhaps also update the
    // models' animations.
    // For now it does nothing :P
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

        drawableObj->CopyModelMatrixTo(modelMatrix);

                                //mjModel& model, float* modelMatrix, float* lookAtMatrix, float* projectionMatrix, mjModelPose* pose, mjMatrixStack* stack)
        renderer.RenderModel(* drawableObj->model, modelMatrix, lookAtMatrix, projectionMatrix, NULL, &matrixStack,
                             drawableObj->customShaders, drawableObj->customTextures, drawableObj->extraColorForTexture, resourceManager->shaderList);

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
