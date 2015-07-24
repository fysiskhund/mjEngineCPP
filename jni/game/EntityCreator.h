//
//  EntityCreator.h
//  mjEngineCPP
//
//  Created by Alejandro Valenzuela Roca on 27/09/14.
//  Copyright (c) 2014-15 Phong-shaded hallucinations. All rights reserved.
//

#ifndef mjEngineCPP_EntityCreator_h
#define mjEngineCPP_EntityCreator_h
#include <string.h>
#include <vector>

#include <extLibs/tinyxml/tinyxml2.h>
#include <extLibs/util/mjXMLHelper.h>
#include <util/mjResourceManager.h>

#include <core/mjObject.h>
#include <physics/mjBoundingStructure.h>

#include "entities/Character.h"
#include "entities/Bird.h"
#include "entities/BatBot.h"
#include "entities/Frog.h"
#include "entities/MysticalDoor.h"

#include "entities/FrogBoss.h"

#include "entities/Plant.h"

#include "ObjectTags.h"


#include "Level.h"





using namespace mjEngine;

class EntityCreator
{
public:
    EntityCreator(mjResourceManager* resourceManager);
    void PopulateLevel(tinyxml2::XMLDocument* levelDoc, Level* levelData);


private:
    mjObject* CreateEntity(const char* entityType, Level* levelData);
    std::vector<const char*> entityTypes;
    mjResourceManager* resourceManager;

};


#endif
