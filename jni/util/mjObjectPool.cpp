#include "mjObjectPool.h"

namespace  mjEngine {


mjObjectPool::mjObjectPool()
{

}

mjObjectPool::~mjObjectPool()
{

}

void mjObjectPool::Initialize(mjResourceManager* resourceManager)
{
    this->resourceManager = resourceManager;
}

void mjObjectPool::AllocateObjects(unsigned howMany)
{
    for (unsigned i = 0; i < howMany; i++)
    {
        mjObject* newObject = CreateNewObject();
        objects.push_back(newObject);
    }
}

mjObject* mjObjectPool::GetAvailableObject()
{
    for (unsigned i = 0; i < objects.size(); i++)
    {
        mjObject* existingObject = objects[i];

        if (existingObject->isAvailableFromPool)
        {
            existingObject->isAvailableFromPool = false;

            return existingObject; // Execution stops here
        }
    }
    mjObject* newObject = CreateNewObject();
    newObject->isAvailableFromPool = false;
    objects.push_back(newObject);

    return newObject;
}


void mjObjectPool::Clean()
{
    // Delete everyone from the array first, then empty it
    for (unsigned i = 0; i < objects.size(); i++)
    {
        delete (objects[i]);
    }

    objects.clear();

}

}
