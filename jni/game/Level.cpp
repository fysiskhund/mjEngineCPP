#include "Level.h"

Level::Level(mjResourceManager* resourceManager)
{
    this->resourceManager = resourceManager;

    mjVector3 initialMinCorner(MJ_OVER_9000, MJ_OVER_9000, MJ_OVER_9000);
    mjVector3 initialMaxCorner(-MJ_OVER_9000, -MJ_OVER_9000, -MJ_OVER_9000);

    bounds = new mjAABB(&levelCenter, initialMinCorner, initialMaxCorner, true);
    LOGI("%s %d: new %s", __FILE__, __LINE__, "mjAABB");
    hardLimits = new mjAABB(*bounds);
    LOGI("%s %d: new %s", __FILE__, __LINE__, "mjAABB");

}

void Level::LoadFromFile(const char* fileName)
{
    checkGlError("LoadFromFile start");

	doc.LoadFile(fileName);
	Load(&doc);
}

void Level::Load(tinyxml2::XMLDocument* doc)
{

	XMLHandle docHandle(doc);

	// Entity load has been implemented in EntityCreator.cpp

	XMLElement* terrainElement = docHandle.FirstChildElement("level").FirstChildElement("terrain").FirstChild().ToElement();
	while (terrainElement)
	{

		mjObject* obj = NULL;

		obj = terrainCreator.CreateTerrain(terrainElement->Name(), * resourceManager);

		if (obj)
		{
			if(obj->boundingStructure->type == MJ_AABB)
			{
				mjAABB* aabb = (mjAABB*) obj->boundingStructure;

                obj->SetID(terrainElement->Attribute("id"));



                mjXMLHelper::ReadVector(terrainElement->FirstChildElement("mincorner"), &aabb->minCorner);
				mjXMLHelper::ReadVector(terrainElement->FirstChildElement("maxcorner"), &aabb->maxCorner);

				if (aabb->minCorner.x < bounds->minCorner.x)
				{
                    bounds->minCorner.x = aabb->minCorner.x;
				}
				if (aabb->minCorner.y < bounds->minCorner.y)
				{
                    bounds->minCorner.y = aabb->minCorner.y;
				}
				if (aabb->minCorner.z < bounds->minCorner.z)
				{
                    bounds->minCorner.z = aabb->minCorner.z;
				}

				if (aabb->maxCorner.x > bounds->maxCorner.x)
				{
                    bounds->maxCorner.x = aabb->maxCorner.x;
				}
				if (aabb->maxCorner.y > bounds->maxCorner.y)
				{
                    bounds->maxCorner.y = aabb->maxCorner.y;
				}
				if (aabb->maxCorner.z > bounds->maxCorner.z)
				{
                    bounds->maxCorner.z = aabb->maxCorner.z;
				}
				obj->SetDetailsFromXML(terrainElement);

                /*LOGI("TerrainElmnt %s (%s) found [%3.3f %3.3f %3.3f] [%3.3f %3.3f %3.3f]", obj->id, terrainElement->Name(),
						aabb->minCorner.x, aabb->minCorner.y, aabb->minCorner.z,
                        aabb->maxCorner.x, aabb->maxCorner.y, aabb->maxCorner.z  );*/
				aabb->UpdateCenter();
                obj->MatchScaleToAABB();
			}
			terrain.push_back(obj);
		}
		terrainElement = terrainElement->NextSiblingElement();
	}

	bounds->UpdateCenter();

	hardLimits->halfWidths.CopyFrom(bounds->halfWidths);

	// Add 30%
	hardLimits->halfWidths.MulScalar(1.0 + hardLimitExtra);
	// Update
	hardLimits->UpdateCorners();



	LOGI("%u entities, %u terrain elements, bounds [%3.3f %3.3f %3.3f] [%3.3f %3.3f %3.3f]; hardLimits [%3.3f %3.3f %3.3f] [%3.3f %3.3f %3.3f]",
         entities.size(), terrain.size(),

         bounds->minCorner.x, bounds->minCorner.y, bounds->minCorner.z,
         bounds->maxCorner.x, bounds->maxCorner.y, bounds->maxCorner.z,

         hardLimits->minCorner.x, hardLimits->minCorner.y, hardLimits->minCorner.z,
         hardLimits->maxCorner.x, hardLimits->maxCorner.y, hardLimits->maxCorner.z
         );
}



mjObject* Level::GetEntityByID(const char* id)
{
    for (unsigned i = 0; i < entities.size(); i++) {
        //LOGI("Searching for %s == %s?", entities[i]->id, id);
        if (strncmp(entities[i]->id, id, 200) == 0) {
            return entities[i];
        }
    }
    LOGI("GetEntityByID: %s: not found!!", id);
    return NULL;
}

void Level::Unload()
{
    // Remove all the entities
    while (entities.size() > 0)
    {
        delete entities[entities.size()-1];
        entities.pop_back();
    }

    while (terrain.size() > 0)
    {
        delete terrain[terrain.size()-1];
        terrain.pop_back();
    }
    levelCenter.Set0();
    delete [] bounds;
    bounds = NULL;

    delete [] hardLimits;
    hardLimits = NULL;

    doc.Clear();
}

Level::~Level()
{
    Unload();
}
