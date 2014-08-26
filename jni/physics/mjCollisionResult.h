/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

#ifndef MJCOLLISIONRESULT_H
#define MJCOLLISIONRESULT_H

#include "mjPhysicsEffect.h"

namespace mjEngine{

enum mjcolresult{
	MJ_NO_COLLISION=0,
	MJ_OVERLAP,
	MJ_UNDER,
	MJ_OVER
};

class mjCollisionResult{
public:
	mjPhysicsEffect* effectObj0;
	mjPhysicsEffect* effectObj1;
};

}

#endif
