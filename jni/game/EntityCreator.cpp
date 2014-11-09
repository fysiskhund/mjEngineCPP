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
}

mjObject* EntityCreator::CreateEntity(const char* entityType, Level* levelData)
{
    int whichEntity = -1;
    unsigned i = 0;

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
            return new Character();
            break;
        case 1:
            return new Bird();
            break;
        case 2:
            return new BatBot(levelData);
            break;
        case 3:
            return new Plant(levelData, *resourceManager);
            break;
        default:
            return NULL;
            break;
    }
}
