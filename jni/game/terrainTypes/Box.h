//
//  Box.h
//  mjEngineCPP
//
//  Created by Alejandro Valenzuela Roca on 27/09/14.
//  Copyright (c) 2014 Phong-shaded hallucinations. All rights reserved.
//

#ifndef BOX_H
#define BOX_H

#include <extLibs/util/mjMultiPlatform.h>

#include <core/mjObject.h>
#include <util/mjResourceManager.h>
#include <extLibs/logger/mjLog.h>


using namespace mjEngine;

class Box: public mjObject
{
public:
	Box(mjResourceManager* resourceManager);

};

#endif
