//
//  Bird.h
//  mjEngineCPP
//
//  Created by Alejandro Valenzuela Roca on 27/09/14.
//  Copyright (c) 2014 Phong-shaded hallucinations. All rights reserved.
//

#ifndef __mjEngineCPP__Bird__
#define __mjEngineCPP__Bird__


#include <extLibs/util/mjMultiPlatform.h>


#include <core/mjObject.h>
#include <util/mjResourceManager.h>
#include <graphics/mjImageLoader.h>

#include "KosmoObject.h"

using namespace mjEngine;

class Bird: public KosmoObject
{
public:
    Bird(Level* levelData, mjResourceManager* resourceManager);
private:
};

#endif /* defined(__mjEngineCPP__Bird__) */
