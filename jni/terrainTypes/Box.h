//
//  Box.h
//  mjEngineCPP
//
//  Created by Alejandro Valenzuela Roca on 27/09/14.
//  Copyright (c) 2014 Phong-shaded hallucinations. All rights reserved.
//

#ifndef BOX_H
#define BOX_H

#include <GLES2/gl2.h>
#include <SDL2/SDL.h>

#include "../core/mjObject.h"
#include "../extLibs/logger/mjLog.h"
#include "../graphics/mjImageLoader.h"


using namespace mjEngine;

class Box: public mjObject
{
public:
	Box();

	char* modelName = NULL;
};

#endif
