/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 
#ifndef MJCOLLISIONTESTS_H
#define MJCOLLISIONTESTS_H

#include "../mjVector3.h"
#include "mjSphere.h"
#include "mjCollisionResult.h"

namespace mjEngine
{



class mjCollisionTests{
public:

	static mjcolresult SphereVsSphere(mjSphere& s0, mjSphere& s1, mjCollisionResult *out);
private:
};


}

#endif
