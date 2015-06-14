#include "MysticalDoor.h"




MysticalDoor::MysticalDoor(Level* levelData, mjResourceManager* resourceManager)
{
    offsetOnTeleportArrive.x = 0.5; // By default, objects arriving to this door will be placed 0.5 units in front in the X axis.
}

void MysticalDoor::SetDetailsFromXML(XMLElement* entity)
{
    mjObject::SetDetailsFromXML(entity);
    counterpartName = entity->Attribute("counterpart");
    mjXMLHelper::ReadVector(entity->FirstChildElement("offsetonteleportarrive"), &offsetOnTeleportArrive);

}

MysticalDoor::~MysticalDoor()
{
    //dtor
}
