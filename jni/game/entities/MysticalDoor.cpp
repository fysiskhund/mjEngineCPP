#include "MysticalDoor.h"




MysticalDoor::MysticalDoor(Level* levelData, mjResourceManager* resourceManager)
    :KosmoObject(MJ_AABB, resourceManager, levelData)
{
    //offsetOnTeleportArrive.z = 1.5; // By default, objects arriving to this door will be placed 0.5 units in front in the Z axis.
    offsetOnTeleportArrive.y = 0.3;
    offsetRadiusOnTeleportArrive = 0.5;

    model = resourceManager->FetchModel("entities/door/door.mesh.xml");

    ((mjAABB*)boundingStructure)->isImmovable = true;

    GLuint glTexture = resourceManager->FetchTexture("entities/door/door.png", GL_REPEAT);//("/sdcard/mjEngineCPP/bluesky/wandering_cloud0.png"); //
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


void MysticalDoor::OnOverlap(mjObject* otherObject)
{
    /*if (otherObject->tag == OT_CHARACTER)
    {
        if (mjCollisionTests::AABBVsAABB((mjAABB*) this->boundingStructure, (mjAABB*) otherObject->boundingStructure, NULL))
            printf("x");
    }*/
}

void MysticalDoor::ProcessCollisionEffects()
{
    if (teleportFunctionActive)
    {
        for (unsigned i=0; i < collisionStack.size(); i++)
        {
            mjPhysicsEffect* collisionEffect = collisionStack[i];

            if (collisionEffect->otherObject->tag > OT_TERRAINTYPESENDMARKERTAG)
            {
                KosmoObject* otherKObject = (KosmoObject*)collisionEffect->otherObject;
                if (otherKObject->canGoThroughDoors  && otherKObject->teleportCooldown <= 0 && counterpart != NULL)
                {
                    mjVector3 directionOnArrival(this->pos);
                    directionOnArrival.Subtract(otherKObject->pos);
                    // For now just remove the "y" component. Later it will have to be transformed to the exit point's orientation
                    directionOnArrival.y = 0;
                    directionOnArrival.Normalize();

                    // Adopt the arrival door's position
                    otherKObject->pos.CopyFrom(counterpart->pos);
                    otherKObject->teleportCooldown = 1;

                    // displace the object by the radius specified, along the directionOnArrival
                    otherKObject->pos.ScaleAdd(counterpart->offsetRadiusOnTeleportArrive, directionOnArrival);

                    // Finally add the static offset
                    otherKObject->pos.Add(counterpart->offsetOnTeleportArrive);

                    if (isCheckpointForPlayer && otherKObject->tag == OT_CHARACTER)
                    {
                        otherKObject->startPosition.CopyFrom(otherKObject->pos);

                    }

                }
            }
        }
    }
    KosmoObject::ProcessCollisionEffects();
}
MysticalDoor::~MysticalDoor()
{
    //dtor
}
