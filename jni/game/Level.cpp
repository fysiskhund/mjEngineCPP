#include "Level.h"


void Level::LoadFromFile(const char* fileName)
{
	XMLDocument doc;

	doc.LoadFile(fileName);
	Load(&doc);
}

void Level::Load(XMLDocument* doc)
{
	XMLHandle docHandle(doc);

	LOGI("Starting level load; scanning for Entities");

	XMLElement* entity = docHandle.FirstChildElement("level").FirstChildElement("entities").FirstChild().ToElement();

	while (entity)
	{
		LOGI("Entity %s found, filling up details", entity->Name());
		mjObject* obj = NULL;
		
        obj = entityCreator.CreateEntity(entity->Name());
        
        if (obj)
        {
            // Read its characteristics
            obj->SetID(entity->Attribute("id"));
            ReadVector(entity->FirstChildElement("pos"), &obj->pos);
            ReadVector(entity->FirstChildElement("dir"), &obj->dir);
            ReadVector(entity->FirstChildElement("up"), &obj->up);
            ReadVector(entity->FirstChildElement("vel"), &obj->vel);
            entities.push_back(obj);
        }

		entity = entity->NextSiblingElement();
	}
	XMLElement* terrainElement = docHandle.FirstChildElement("level").FirstChildElement("terrain").FirstChild().ToElement();
	while (terrainElement)
	{

		mjObject* obj = NULL;

		obj = terrainCreator.CreateTerrain(terrainElement->Name());

		if (obj)
		{
			if(obj->boundingStructure->type == MJ_AABB)
			{
				mjAABB* aabb = (mjAABB*) obj->boundingStructure;

                obj->SetID(terrainElement->Attribute("id"));



				ReadVector(terrainElement->FirstChildElement("mincorner"), &aabb->minCorner);
				ReadVector(terrainElement->FirstChildElement("maxcorner"), &aabb->maxCorner);

				LOGI("TerrainElement %s found [%3.3f %3.3f %3.3f] [%3.3f %3.3f %3.3f]", terrainElement->Name(),
						aabb->minCorner.x, aabb->minCorner.y, aabb->minCorner.z,
						aabb->maxCorner.x, aabb->maxCorner.y, aabb->maxCorner.z  );
				aabb->UpdateCenter();
                obj->MatchScaleToAABB();
			}
			terrain.push_back(obj);
		}
		terrainElement = terrainElement->NextSiblingElement();
	}
	LOGI("%d entities, %d terrain elements", entities.size(), terrain.size());
}

void Level::ReadVector(XMLElement* element, mjVector3* v)
{
    if (element)
    {
        element->QueryFloatAttribute("x", &v->x);
        element->QueryFloatAttribute("y", &v->y);
        element->QueryFloatAttribute("z", &v->z);
    }
}

mjObject* Level::GetEntityByID(const char* id)
{
    for (int i = 0; i < entities.size(); i++) {
    	LOGI("Searching for %s == %s?", entities[i]->id, id);
        if (strncmp(entities[i]->id, id, 200) == 0) {
            return entities[i];
        }
    }
    return NULL;
}


