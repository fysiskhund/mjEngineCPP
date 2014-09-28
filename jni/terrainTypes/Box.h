//
//  Box.h
//  mjEngineCPP
//
//  Created by Alejandro Valenzuela Roca on 27/09/14.
//  Copyright (c) 2014 Phong-shaded hallucinations. All rights reserved.
//

#ifndef BOX_H
#define BOX_H

#include "../core/mjObject.h"
#include "../extLibs/logger/mjLog.h"


using namespace mjEngine;

class Box: public mjObject
{
public:
	Box();
	char* modelName = NULL;
};

#endif
