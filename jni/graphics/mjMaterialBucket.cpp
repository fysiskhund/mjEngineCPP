#include "mjMaterialBucket.h"

namespace mjEngine {

mjMaterialBucket::mjMaterialBucket(mjObject* exampleObject, mjResourceManager* resourceManager, bool addObject)
{
    this->resourceManager = resourceManager;
    /*for (unsigned i = 0; i < 4; i++)
    {
        extraColorForTexture[i] = exampleObject->extraColorForTexture[i];
    }*/

    if (exampleObject->model != NULL)
    {

        if (exampleObject->customTextures != NULL)
        {
            this->texture = exampleObject->customTextures[0]; // hmm.. maybe have a texture array? FIXME!
        } else
        {
            // Get the texture from the model
            this->texture = exampleObject->model->meshes[0]->glTexture; // FIXME
        }
        if (exampleObject->customShaders != NULL)
        {
            this->shader = (*exampleObject->customShaders)[0]; // For now no object is using more than one shader. FIXME when they start doing it.
        } else
        {
            int shaderListIndex = exampleObject->model->meshes[0]->mjShaderListIndex;
            this->shader = resourceManager->shaderList[shaderListIndex];
        }
    } else
    {
        isNullMaterialBucket = true;

    }
    if (addObject)
    {
        objects.push_back(exampleObject);
    }
}

mjMaterialBucket::~mjMaterialBucket()
{
    objects.clear();
}

mjMaterialBucket* mjMaterialBucket::AddObjectIfItBelongs(mjObject* object)
{


    if (TestIfObjectBelongs(object))
    {
        objects.push_back(object);
        return this;
    }
    return nullptr;
}

mjMaterialBucket* mjMaterialBucket::ForceAddObject(mjObject* object)
{
    objects.push_back(object);
    return this;
}

bool mjMaterialBucket::RemoveObject(mjObject* object, bool forceRemove)
{
    if (forceRemove || TestIfObjectBelongs(object))
    {
        std::vector<mjObject*>::iterator it = objects.begin();
        std::vector<mjObject*>::iterator end = objects.end();

        while (it != end)
        {
            if (*it == object)
            {
                objects.erase(it);
                return true;
            }
            it++;
        }

    }
    return false;
}

bool mjMaterialBucket::TestIfObjectBelongs(mjObject* exampleObject)
{
    unsigned int objectTexture;
    mjShader* objectShader;

    if (exampleObject->model != NULL)
    {
        if (exampleObject->customTextures != NULL)
        {
            objectTexture = exampleObject->customTextures[0]; // hmm.. maybe have a texture array? FIXME!
        } else
        {
            // Get the texture from the model
            objectTexture = exampleObject->model->meshes[0]->glTexture; // FIXME
        }

        if (objectTexture != this->texture)
        {
            return false;
        }

        if (exampleObject->customShaders != NULL)
        {
            objectShader = (*exampleObject->customShaders)[0]; // For now no object is using more than one shader. FIXME when they start doing it.
        } else
        {
            int shaderListIndex = exampleObject->model->meshes[0]->mjShaderListIndex;
            objectShader = resourceManager->shaderList[shaderListIndex];
        }
    } else if (isNullMaterialBucket)
    {
        return true;

    }


    return (this->shader == objectShader);
}

}
