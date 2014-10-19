//
//  EntityCreator.h
//  mjEngineCPP
//
//  Created by Alejandro Valenzuela Roca on 27/09/14.
//  Copyright (c) 2014 Phong-shaded hallucinations. All rights reserved.
//

#ifndef mjEngineCPP_EntityCreator_h
#define mjEngineCPP_EntityCreator_h
#include <string.h>
#include <vector>

#include "../extLibs/tinyxml/tinyxml2.h"
#include "../extLibs/util/mjXMLHelper.h"

#include "../core/mjObject.h"
#include "../physics/mjBoundingStructure.h"
#include "../entities/Character.h"
#include "../entities/Bird.h"
#include "../entities/BatBot.h"
#include "../entities/Grass.h"

#include "Level.h"





using namespace mjEngine;

class EntityCreator
{
public:
    EntityCreator();
    void PopulateLevel(XMLDocument* levelDoc, Level* levelData);


private:
    mjObject* CreateEntity(const char* entityType, Level* levelData);
    std::vector<const char*> entityTypes;

};


#endif
