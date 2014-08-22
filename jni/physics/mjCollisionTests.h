/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 
#ifndef MJCOLLISIONTESTS_H
#define MJCOLLISIONTESTS_H

#include "../mjVector3.h"
#include "mjCollisionResult.h"
#include "mjSphere.h"
#include "mjAABB.h"


namespace mjEngine
{



class mjCollisionTests{
public:

	static mjcolresult SphereVsSphere(mjSphere& s0, mjSphere& s1, mjCollisionResult* out);
	
	static mjcolresult AABBVsAABB(mjAABB& a, mjAABB& b, mjCollisionResult* out);
private:
};


}

#endif
