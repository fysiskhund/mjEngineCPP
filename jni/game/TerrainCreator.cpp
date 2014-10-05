#include "TerrainCreator.h"

TerrainCreator::TerrainCreator()
{
	terrainTypes.push_back("box");
}

mjObject* TerrainCreator::CreateTerrain(const char* terrainType)
{
    int whichTerrainType = -1;
    int i = 0;

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
            return new Box();
            break;


        default:
            return NULL;
            break;
    }
}
