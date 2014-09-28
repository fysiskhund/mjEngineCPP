//
//  EntityCreator.cpp
//  mjEngineCPP
//
//  Created by Alejandro Valenzuela Roca on 27/09/14.
//  Copyright (c) 2014 Phong-shaded hallucinations. All rights reserved.
//

#include "entityCreator.h"

using namespace mjEngine;

EntityCreator::EntityCreator()
{
    entityTypes.push_back("player");
    entityTypes.push_back("bird");
    
}

mjObject* EntityCreator::CreateEntity(const char* entityType)
{
    int whichEntity = -1;
    int i = 0;
    
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
            
        default:
            return NULL;
            break;
    }
}
