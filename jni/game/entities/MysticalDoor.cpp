#include "MysticalDoor.h"




MysticalDoor::MysticalDoor(Level* levelData, mjResourceManager* resourceManager)
    :KosmoObject(MJ_AABB, resourceManager, levelData)
{
    offsetOnTeleportArrive.z = 0.5; // By default, objects arriving to this door will be placed 0.5 units in front in the Z axis.
}

void MysticalDoor::SetDetailsFromXML(XMLElement* entity)
{
    KosmoObject::SetDetailsFromXML(entity);
    counterpartName = entity->Attribute("counterpart");
    mjXMLHelper::ReadVector(entity->FirstChildElement("offsetonteleportarrive"), &offsetOnTeleportArrive);

}
void MysticalDoor::ProcessCollisionEffects()
{
    for (unsigned i=0; i < collisionStack.size(); i++)
    {
        mjPhysicsEffect* collisionEffect = collisionStack[i];
        KosmoObject* otherKObject = (KosmoObject*)collisionEffect->otherObject;
        if (otherKObject->canGoThroughDoors && this->counterpart != NULL)
        {
            otherKObject->pos.CopyFrom(counterpart->pos);
            otherKObject->pos.Add(counterpart->offsetOnTeleportArrive);
        }
    }
    KosmoObject::ProcessCollisionEffects();
}
MysticalDoor::~MysticalDoor()
{
    //dtor
}
