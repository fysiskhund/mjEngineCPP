#include "Level.h"


void Level::LoadFromFile(const char* fileName)
{


	doc.LoadFile(fileName);
	Load(&doc);
}

void Level::Load(XMLDocument* doc)
{
	XMLHandle docHandle(doc);

	// Entity load has been implemented in EntityCreator.cpp

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



                mjXMLHelper::ReadVector(terrainElement->FirstChildElement("mincorner"), &aabb->minCorner);
				mjXMLHelper::ReadVector(terrainElement->FirstChildElement("maxcorner"), &aabb->maxCorner);

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
	LOGI("%ld entities, %ld terrain elements", entities.size(), terrain.size());
}



mjObject* Level::GetEntityByID(const char* id)
{
    for (unsigned i = 0; i < entities.size(); i++) {
    	LOGI("Searching for %s == %s?", entities[i]->id, id);
        if (strncmp(entities[i]->id, id, 200) == 0) {
            return entities[i];
        }
    }
    return NULL;
}


