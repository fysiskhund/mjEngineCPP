#include "mjSceneGraph.h"

namespace mjEngine
{

void mjSceneGraph::Initialize(mjResourceManager* resourceManager)
{
    this->resourceManager = resourceManager;
}

void mjSceneGraph::Add(mjObject* object, bool isDrawable, bool castsShadow, bool isTranslucent)
{
    if (isDrawable)
    {
        object->sceneGraphDrawablesIndex = drawableObjects.size();
        drawableObjects.push_back(object);

        object->sceneGraphTranslucentsIndex = translucentObjects.max_size(); // Mark index as invalid.
    } else if (isTranslucent)
    {

        object->sceneGraphTranslucentsIndex = translucentObjects.size();
        translucentObjects.push_back(object);

        object->sceneGraphDrawablesIndex = drawableObjects.max_size(); // Mark index as invalid.
    }
    if (castsShadow)
    {
        object->sceneGraphShadowCastersIndex = shadowCasters.size();
        shadowCasters.push_back(object);
    } else
    {
        object->sceneGraphShadowCastersIndex = shadowCasters.max_size(); // Mark index as invalid.
    }


}
/*
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
    for (unsigned i = 0; i < group->size(); i++)
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
}*/

bool mjSceneGraph::Remove(mjObject* objToRemove, bool fromDrawables, bool fromShadowCasters, bool fromTranslucents)
{
    bool actionTaken = false;

    if (fromDrawables)
    {
        if (RemoveFromVectorWithIndex(&drawableObjects, objToRemove, objToRemove->sceneGraphDrawablesIndex))
        {
            objToRemove->sceneGraphDrawablesIndex = drawableObjects.max_size();
            actionTaken = true;
        }
    }
    if (fromTranslucents)
    {
        if (RemoveFromVectorWithIndex(&translucentObjects, objToRemove, objToRemove->sceneGraphTranslucentsIndex))
        {
            objToRemove->sceneGraphTranslucentsIndex = translucentObjects.max_size();
            actionTaken = true;
        }
    }
    if (fromShadowCasters)
    {
        if (RemoveFromVectorWithIndex(&shadowCasters, objToRemove, objToRemove->sceneGraphShadowCastersIndex))
        {
            objToRemove->sceneGraphShadowCastersIndex = shadowCasters.max_size();
            actionTaken = true;
        }
    }

    return actionTaken;


}

bool mjSceneGraph::RemoveThorough(mjObject* objToRemove, bool inDrawables, bool inShadowCasters, bool inTranslucent)
{

    bool result = false;
    if (inDrawables)
    {
        result = RemoveFromVector(&drawableObjects, objToRemove);
    }
    if (inShadowCasters)
    {
        result = result || RemoveFromVector(&shadowCasters, objToRemove);
    }
    if (inTranslucent)
    {
        result = result || RemoveFromVector(&translucentObjects, objToRemove);
    }

    return result;
}

void mjSceneGraph::Update(float t_elapsed)
{
    // This is supposed to optimise drawing by culling objects that are not visible. Perhaps also update the
    // models' animations.
    // For now it does nothing :P
}



void mjSceneGraph::Draw(mjCamera* camera, std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix)
{
    this->lookAtMatrix = lookAtMatrix;
    this->projectionMatrix = projectionMatrix;

    matrixStack.PopAll();
    Matrix4::SetIdentityM(matrixStack.current, 0);

    unsigned numObjects = drawableObjects.size();
	for (unsigned i= 0 ; i < numObjects; i++)
	{
        mjObject* drawableObj = drawableObjects[i];
        DrawObject(drawableObj);

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
void mjSceneGraph::DrawObject(mjObject* objToDraw)
{
    float modelMatrix[16];
    objToDraw->CopyModelMatrixTo(modelMatrix);

    matrixStack.Push(modelMatrix);


    if (objToDraw->model)
    {
        //                     mjModel& model, float* modelMatrix, float* lookAtMatrix, float* projectionMatrix, mjModelPose* pose, mjMatrixStack* stack)
        renderer.RenderModel(* objToDraw->model, matrixStack.current, lookAtMatrix, projectionMatrix, NULL, &matrixStack,
                             objToDraw->customShaders, objToDraw->customTextures, objToDraw->extraColorForTexture, resourceManager->shaderList);
    }

    unsigned drawToSubObject = objToDraw->drawToSubObject > -1 ? objToDraw->drawToSubObject : objToDraw->subObjects.size();

    if (drawToSubObject > 0)
    {
        for (int i = 0; i < drawToSubObject; i++)
        {
            DrawObject(objToDraw->subObjects[i]);
        }

    }
    matrixStack.Pop();

}

bool mjSceneGraph::RemoveFromVector(std::vector<mjObject*>* vectorObj, mjObject* object)
{

    std::vector<mjObject*>::iterator end = vectorObj->end();

    for (std::vector<mjObject*>::iterator j = vectorObj->begin(); j != end; j++)
    {
        if (object == *j)
        {
            vectorObj->erase(j);
            return true;
            //break; // Not necessary after "return"
        }
    }
    return false;
}

bool mjSceneGraph::RemoveFromVectorWithIndex(std::vector<mjObject*>* vectorObj, mjObject* object, unsigned index)
{

    std::vector<mjObject*>::iterator j = vectorObj->begin();

    j += index;

    if (*j == object)
    {
        vectorObj->erase(j);

        return true;
    }
    return false;
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
