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
	mjcolresult result;
	mjPhysicsEffect* relocationEffectObj0;
	mjPhysicsEffect* changeVelEffectObj0;
	mjPhysicsEffect* accelObj0;
	mjPhysicsEffect* relocationEffectObj1;
	mjPhysicsEffect* changeVelEffectObj1;
	mjPhysicsEffect* accelObj1;

	mjCollisionResult();
};

}

#endif
