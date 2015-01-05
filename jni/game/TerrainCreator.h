//
//  TerrainCreator.h
//  mjEngineCPP
//
//  Created by Alejandro Valenzuela Roca on 27/09/14.
//  Copyright (c) 2014 Phong-shaded hallucinations. All rights reserved.
//

#ifndef mjEngineCPP_TerrainCreator_h
#define mjEngineCPP_TerrainCreator_h

#include <string.h>
#include <vector>

#include "../core/mjObject.h"
#include "../util/mjResourceManager.h"
#include "../physics/mjBoundingStructure.h"
#include "../terrainTypes/Box.h"
#include "../terrainTypes/FallingBox.h"


using namespace mjEngine;



class TerrainCreator
{
public:
	TerrainCreator();
    mjObject* CreateTerrain(const char* terrainType, mjResourceManager& resourceManager);

private:

    std::vector<const char*> terrainTypes;
};


#endif

