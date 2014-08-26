#include "mjCollisionTests.h"

namespace mjEngine{
mjcolresult mjCollisionTests::SphereVsSphere(mjSphere& s0, mjSphere& s1, mjCollisionResult *out){
	mjVector3 s0ToS1(s1.c);

	s0ToS1.Subtract(s0.c);

	float dist = s0ToS1.Normalize();
	float rSum = s0.r+s1.r;

	if (dist < rSum)
	{
		if (out != NULL)
		{
			float distHalf = 0.5*dist;

			out->effectObj0 = new mjPhysicsEffect();
			out->effectObj0->type = MJ_COLLISION;
			out->effectObj0->action = MJ_CHANGE_POSITION;

			s0ToS1.MulScalar(distHalf);

			out->effectObj0->value.CopyFrom(s0ToS1);



			out->effectObj1 = new mjPhysicsEffect();
			out->effectObj1->type = MJ_COLLISION;
			out->effectObj1->action = MJ_CHANGE_POSITION;

			s0ToS1.MulScalar(-1);

			out->effectObj1->value.CopyFrom(s0ToS1);

		}
		return MJ_OVERLAP;
	} else
	{
		return MJ_NO_COLLISION;
	}

}
}
