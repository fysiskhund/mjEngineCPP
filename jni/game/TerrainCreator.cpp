#include "TerrainCreator.h"

TerrainCreator::TerrainCreator()
{

	terrainTypes.push_back("box");
	terrainTypes.push_back("fallingbox");
    terrainTypes.push_back("triggerbox");
}

mjObject* TerrainCreator::CreateTerrain(const char* terrainType, mjResourceManager& resourceManager)
{
    int whichTerrainType = -1;
    int i = 0;
    mjObject* obj = NULL;

    while(whichTerrainType == -1 && i < terrainTypes.size())
    {
        if (strncmp(terrainType, terrainTypes[i], 128) == 0)
        {
        	whichTerrainType = i;
        }
        i++;
    }
    switch (whichTerrainType) {
        case 0:
            obj = new Box(&resourceManager);
            LOGI("%s %d: new %s", __FILE__, __LINE__, "Box (terrain)");

            obj->tag = OT_BOX;
            break;
        case 1:
            obj = new FallingBox(&resourceManager);
            LOGI("%s %d: new %s", __FILE__, __LINE__, "fallingBox (terrain)");

            obj->tag = OT_FALLINGBOX;
            break;
        case 2:
            obj = new TriggerBox(&resourceManager);
            LOGI("%s %d: new %s", __FILE__, __LINE__, "triggerBox (terrain)");

            obj->tag = OT_TRIGGERBOX;
        break;



        default:
            return NULL;
            break;
    }

    return obj;
}
