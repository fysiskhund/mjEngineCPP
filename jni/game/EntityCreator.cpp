//
//  EntityCreator.cpp
//  mjEngineCPP
//
//  Created by Alejandro Valenzuela Roca on 27/09/14.
//  Copyright (c) 2014 Phong-shaded hallucinations. All rights reserved.
//

#include "EntityCreator.h"

EntityCreator::EntityCreator(mjResourceManager* resourceManager)
{
    this->resourceManager = resourceManager;
    entityTypes.push_back("player");
    entityTypes.push_back("bird");
    entityTypes.push_back("bat");
    entityTypes.push_back("plant");
    entityTypes.push_back("frog");
    entityTypes.push_back("door");

}

void EntityCreator::PopulateLevel(XMLDocument* levelDoc, Level* levelData)
{


    XMLHandle docHandle(levelDoc);
    LOGI("Scanning for Entities");

	XMLElement* entity = docHandle.FirstChildElement("level").FirstChildElement("entities").FirstChild().ToElement();

	while (entity)
	{
		LOGI("Entity %s found, filling up details", entity->Name());
		mjObject* obj = NULL;

        obj = CreateEntity(entity->Name(), levelData);

        if (obj)
        {
            // Read its characteristics
            obj->SetDetailsFromXML(entity);
            levelData->entities.push_back(obj);
        }

		entity = entity->NextSiblingElement();
	}

	// Tie the doors to their counterparts
	for (unsigned i = 0; i < levelData->entities.size(); i++)
	{
		if (levelData->entities[i]->tag == 5)
		{
            MysticalDoor* door = (MysticalDoor*) levelData->entities[i];

            if (!door->counterpartName.empty())
            {
                if (!door->counterpartName.compare("endlevel") == 0)
                {
                    MysticalDoor* counterPart = (MysticalDoor*) levelData->GetEntityByID(door->counterpartName.c_str());
                    if (counterPart)
                    {
                        door->counterpart = counterPart;
                    } else
                    {
                        LOGI("** Error: door %s without a counterpart (%s)\n", door->id, door->counterpartName.c_str());
                    }
                }
            } else
            {
                LOGI("** Error: door %s does not specify any counterpart\n", door->id);
            }
        }

	}
}

mjObject* EntityCreator::CreateEntity(const char* entityType, Level* levelData)
{
    int whichEntity = -1;
    unsigned i = 0;

    mjObject* result;

    while(whichEntity == -1 && i < entityTypes.size())
    {
        if (strncmp(entityType, entityTypes[i], 128) == 0)
        {
            whichEntity = i;
        }
        i++;
    }
    switch (whichEntity) {
        case 0:
            result = new Character(resourceManager);
            break;
        case 1:
            result = new Bird(resourceManager);
            break;
        case 2:
            result = new BatBot(levelData, resourceManager);
            break;
        case 3:
            result = new Plant(levelData, resourceManager);
            break;
        case 4:
            result = new Frog(levelData, resourceManager);
            break;
        case 5:
            result = new MysticalDoor(levelData, resourceManager);
            break;
        default:
            result = NULL;
            break;
    }
    if (result)
    {
    	result->tag = whichEntity;
    }
    return result;
}
