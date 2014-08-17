#ifndef MJCOLLISIONTESTS
#define MJCOLLISIONTESTS

#include "../mjVector3.h"
#include "mjSphere.h"

enum mjcolresult{
	MJ_NO_COLLISION=0,
	MJ_OVERLAP,
	MJ_UNDER,
	MJ_OVER

};

namespace mjCollisionTests
{

class mjCollisionTests{
public:
	static mjcolresult SphereVsSphere(mjSphere& s0, mjSphere& s1, mjCollisionResult *out);
private:
};


}

#endif
