#include "mjSceneGraph.h"

namespace mjEngine
{

void mjSceneGraph::Initialize(mjResourceManager* resourceManager)
{
    this->resourceManager = resourceManager;
}

void mjSceneGraph::Add(mjObject* object, bool isDrawable, bool castsShadow, bool isTranslucent)
{
    if (object->sceneGraph == nullptr)
    {
        if (isDrawable )
        {

            drawableMatrixOrder.push_back(object);
            //LOGI("Adding object 0x%x", object);
            mjMaterialBucket* bucketFound = nullptr; // Nooo they stole mah bukkit!! I miss mah bukkit!!
            unsigned int i  = 0;


            // Bukkit search party
            while (!bucketFound && i < byMaterial.size())
            {
                if (!simpleDrawList)
                {
                    bucketFound = byMaterial[i]->AddObjectIfItBelongs(object); // Is this mah bukkit?
                } else
                {
                    bucketFound = byMaterial[i]->ForceAddObject(object);
                }
                i++;
            }

            if (!bucketFound) // I could not find mah bukkit :'{(
            {
                bucketFound = new mjMaterialBucket(object, resourceManager); // I haz a new bukkit! :'{D

                byMaterial.push_back(bucketFound);

            }

            object->sceneGraph = this;
            object->sceneGraphActionState = 1 ; // Added, no further action needed.
            object->rendererCalculationState = 0;
            object->rendererBucket = bucketFound;

            int drawToSubObject = object->drawToSubObject;

            if (drawToSubObject >= 0)
            {
                for (int i = 0; i <= drawToSubObject; i++)
                {
                    Add(object->subObjects[i]);
                }
            }


        } else if (isTranslucent)
        {

            //object->sceneGraphTranslucentsIndex = translucentObjects.size();  NOTE: doesn't work. Left there in case I can think of something to make it work
            translucentObjects.push_back(object);

            //object->sceneGraphDrawablesIndex = drawableObjects.max_size(); // Mark index as invalid.  NOTE: doesn't work. Left there in case I can think of something to make it work
        }
        if (castsShadow)
        {
            //object->sceneGraphShadowCastersIndex = shadowCasters.size();  NOTE: doesn't work. Left there in case I can think of something to make it work
            shadowCasters.push_back(object);
        }/* else
    {
     NOTE: doesn't work. Left there in case I can think of something to make it work
        object->sceneGraphShadowCastersIndex = shadowCasters.max_size(); // Mark index as invalid.
    }*/
    } else
    {
        LOGI("Warning: Object %s already has a scenegraph. Not added.", object->id);
    }



}

void mjSceneGraph::Reclassify(mjObject* object)
{
    if (!object->rendererBucket->TestIfObjectBelongs(object))
    {
        Remove(object);
        Add(object);

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

/*
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


}*/

bool mjSceneGraph::Remove(mjObject* objToRemove, bool fromDrawables, bool fromShadowCasters, bool fromTranslucents)
{

    bool actionTaken = false;
    if (fromDrawables && objToRemove->sceneGraph == this)
    {

        RemoveFromVector(&drawableMatrixOrder, objToRemove);


        objToRemove->sceneGraphActionState = 0; // Removed
        objToRemove->sceneGraph = NULL;         // disconnect the SceneGraph
        objToRemove->rendererCalculationState = 0;
        //LOGI("Removing object 0x%x", objToRemove);

        actionTaken = objToRemove->rendererBucket->RemoveObject(objToRemove, true);
        objToRemove->rendererBucket = nullptr;

        if (actionTaken)
        {
            for (unsigned int j = 0; j < objToRemove->subObjects.size(); j++)
            {

                Remove(objToRemove->subObjects[j]); // Remove all the children
            }

        }

    }
    if (fromShadowCasters)
    {
        actionTaken = actionTaken || RemoveFromVector(&shadowCasters, objToRemove);
    }
    if (fromTranslucents)
    {
        actionTaken = actionTaken || RemoveFromVector(&translucentObjects, objToRemove);
    }

    return actionTaken;
}

/*bool mjSceneGraph::RemoveFromBack(mjObject* objToRemove, bool fromDrawables, bool fromShadowCasters, bool fromTranslucents)
{

    bool actionTaken = false;
    if (fromDrawables)
    {
        //actionTaken = RemoveFromVectorFromBack(&drawableObjects, objToRemove);
    }
    if (fromShadowCasters)
    {
        actionTaken = actionTaken || RemoveFromVectorFromBack(&shadowCasters, objToRemove);
    }
    if (fromTranslucents)
    {
        actionTaken = actionTaken || RemoveFromVectorFromBack(&translucentObjects, objToRemove);
    }

    return actionTaken;
}*/

/*unsigned mjSceneGraph::GetUnusedIndexValue() NOTE: Doesn't work. kept around to see if I can make it work.
{
    return drawableObjects.max_size();
}*/

void mjSceneGraph::Update(double t_elapsed)
{
    // This is supposed to optimise drawing by culling objects that are not visible. Perhaps also update the
    // models' animations.
    // For now it does nothing :P
}



void mjSceneGraph::Draw(mjCamera* camera, std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix)
{
    //renderer.StartCountingStateSwitches();
    this->lookAtMatrix = lookAtMatrix;
    this->projectionMatrix = projectionMatrix;

    unsigned numObjects;

    matrixStack.PopAll();
    Matrix4::SetIdentityM(matrixStack.current, 0);

    unsigned drawableMatrixOrderSize = drawableMatrixOrder.size();
    for (unsigned j = 0; j < drawableMatrixOrderSize; j++)
    {
        CalculateMatrices(drawableMatrixOrder[j]);
    }

    unsigned numBuckets = byMaterial.size();

    for (unsigned j = 0; j < numBuckets; j++)
    {
        mjMaterialBucket* zeBucket = byMaterial[j];
        numObjects = zeBucket->objects.size();
        for (unsigned i= 0 ; i < numObjects; i++)
        {
            mjObject* drawableObj = zeBucket->objects[i];
            DrawObject(drawableObj);

            //drawableObjects[i]->Draw(shaderList, lookAtMatrix, projectionMatrix, &matrixStack);
        }
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

    renderer.StopCountingStateSwitches();
}

/*void mjSceneGraph::AutoAddRemoveObject(mjObject* object)
{
    // Determine visibility according to its sceneGraphActionState variable
    switch(object->sceneGraphActionState)
    {
    case 0:
        // Add to the buckets etc
        Add(object);
        break;
    case 1:
        // Nothing
        break;
    case 2:
        // Remove from buckets
        Remove(object);
        break;
    case 3:
        // Nothing
        break;
    }
}*/



void mjSceneGraph::CalculateMatrices(mjObject* object, bool isSubObjectPass)
{


    if (object->rendererCalculationState == 0 || isSubObjectPass) // 0: Calculations not yet performed on this object
    {
        //LOGI("Calculating matrices for 0x%x", object);
        object->rendererCalculationState = 1; // Calculations have been performed on this thang

        float modelMatrix[16];
        object->CopyModelMatrixTo(modelMatrix);
        Matrix4::MultiplyMM(object->rendererMatrix, 0, matrixStack.current, 0, modelMatrix, 0);





        int drawToSubObject = object->drawToSubObject;

        if (drawToSubObject >= 0)
        {
            matrixStack.Insert(object->rendererMatrix); // Equivalent of Push, in this context
            for (int i = 0; i <= drawToSubObject; i++)
            {
                CalculateMatrices(object->subObjects[i], true);
            }

            matrixStack.Pop();
        }
    }
}


void mjSceneGraph::DrawObject(mjObject* objToDraw)
{

#ifdef DEBUGONBEFOREDRAW
    objToDraw->DEBUGonBeforeDraw();
#endif

    if (objToDraw->model)
    {
        //                     mjModel& model, float* modelMatrix, float* lookAtMatrix, float* projectionMatrix, mjModelPose* pose, mjMatrixStack* stack)
        renderer.RenderModel(* objToDraw->model, objToDraw->rendererMatrix, lookAtMatrix, projectionMatrix, NULL, &matrixStack,
                             objToDraw->customShaders, objToDraw->customTextures, objToDraw->customMeshes,
                             objToDraw->extraColorForTexture, resourceManager->shaderList);


    }
    objToDraw->rendererCalculationState = 0;

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

bool mjSceneGraph::RemoveFromVectorFromBack(std::vector<mjObject*>* vectorObj, mjObject* object)
{

    std::vector<mjObject*>::iterator end = vectorObj->end();
    std::vector<mjObject*>::iterator beginning = vectorObj->begin();

    for (std::vector<mjObject*>::iterator j = end; j != beginning; j--)
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

    LOGI("Removing object with index %d", index);
    if (*j == object)
    {
        vectorObj->erase(j);

        return true;
    }
    return false;
}

void mjSceneGraph::CleanUp()
{
    // Disconnect all from mjSceneGraph
    unsigned end = drawableMatrixOrder.size();
    for (unsigned i = 0; i < end; i++)
    {
        mjObject* objToRemove = drawableMatrixOrder[i];

        objToRemove->sceneGraphActionState = 0; // Removed
        objToRemove->sceneGraph = NULL;         // disconnect the SceneGraph
        objToRemove->rendererCalculationState = 0;
    }

    drawableMatrixOrder.clear();
    byMaterial.clear();
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
