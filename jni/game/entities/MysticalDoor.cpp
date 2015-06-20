#include "MysticalDoor.h"




MysticalDoor::MysticalDoor(Level* levelData, mjResourceManager* resourceManager)
    :KosmoObject(MJ_AABB, resourceManager, levelData)
{
    offsetOnTeleportArrive.z = 1.5; // By default, objects arriving to this door will be placed 0.5 units in front in the Z axis.
    offsetOnTeleportArrive.y = 0.5;

    model = resourceManager->FetchModel("door.mesh.xml");

    ((mjAABB*)boundingStructure)->isImmovable = true;

    GLuint glTexture = resourceManager->FetchTexture("door.png", GL_REPEAT);//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
    for (unsigned i = 0; i < model->meshes.size(); i++)
    {
        model->meshes[i]->glTexture = glTexture;
    }



}

void MysticalDoor::SetDetailsFromXML(XMLElement* entity)
{
    KosmoObject::SetDetailsFromXML(entity);
    counterpartName = entity->Attribute("counterpart");
    mjXMLHelper::ReadVector(entity->FirstChildElement("offsetonteleportarrive"), &offsetOnTeleportArrive);

    MatchAABBToModel();

}

void MysticalDoor::DEBUGonCollisionTestStart(mjObject* otherObject)
{
    /*if (otherObject->tag == OT_CHARACTER)
    {
        if (mjCollisionTests::AABBVsAABB((mjAABB*) this->boundingStructure, (mjAABB*) otherObject->boundingStructure, NULL))
            printf("x");
    }*/
}


void MysticalDoor::DEBUGonCollisionOccurred(mjObject* otherObject)
{
    /*if (otherObject->tag == OT_CHARACTER)
    {
        if (mjCollisionTests::AABBVsAABB((mjAABB*) this->boundingStructure, (mjAABB*) otherObject->boundingStructure, NULL))
            printf("x");
    }*/
}

void MysticalDoor::ProcessCollisionEffects()
{
    for (unsigned i=0; i < collisionStack.size(); i++)
    {
        mjPhysicsEffect* collisionEffect = collisionStack[i];
        if (collisionEffect->otherObject->tag > OT_TERRAINTYPESENDMARKERTAG)
        {
            KosmoObject* otherKObject = (KosmoObject*)collisionEffect->otherObject;
            if (otherKObject->canGoThroughDoors && this->counterpart != NULL)
            {
                otherKObject->pos.CopyFrom(counterpart->pos);
                otherKObject->pos.Add(counterpart->offsetOnTeleportArrive);
            }
        }
    }
    KosmoObject::ProcessCollisionEffects();
}
MysticalDoor::~MysticalDoor()
{
    //dtor
}
