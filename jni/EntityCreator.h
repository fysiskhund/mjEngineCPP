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

#include "core/mjObject.h"
#include "physics/mjBoundingStructure.h"
#include "entities/Character.h"
#include "entities/Bird.h"

using namespace mjEngine;

class EntityCreator
{
public:
    EntityCreator();
    mjObject* CreateEntity(const char* entityType);
    
private:
    std::vector<const char*> entityTypes;
};


#endif
