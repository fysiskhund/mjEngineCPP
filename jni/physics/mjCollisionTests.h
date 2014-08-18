#ifndef MJCOLLISIONTESTS
#define MJCOLLISIONTESTS

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
