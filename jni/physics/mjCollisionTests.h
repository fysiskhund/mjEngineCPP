/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */


#ifndef MJCOLLISIONTESTS_H
#define MJCOLLISIONTESTS_H

#include <math.h>
#include <vector>

#include "../core/mjVector3.h"
#include "mjCollisionResult.h"
#include "mjSphere.h"
#include "mjAABB.h"
#include "../extLibs/math/mjMathHelper.h"

#include "../extLibs/logger/mjLog.h"


namespace mjEngine
{



class mjCollisionTests{
public:

    static mjcolresult SphereVsSphere(mjSphere* s0, mjSphere* s1, mjCollisionResult* out);

    static mjcolresult AABBVsAABB(mjAABB* a, mjAABB* b, mjCollisionResult* out);

    static mjcolresult SphereVsAABB(mjSphere* s0, mjAABB* aabb0, mjCollisionResult* out);

private:
};
}

#endif
