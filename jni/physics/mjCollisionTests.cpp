#include "mjCollisionTests.h"

namespace mjEngine{
mjcolresult mjCollisionTests::SphereVsSphere(mjSphere& s0, mjSphere& s1, mjCollisionResult *out){
	float distSq = s0.c.DistanceSquaredTo(s1.c);
	float rSum = s0.r+s1.r;
	return (distSq < (rSum*rSum));

}
}
