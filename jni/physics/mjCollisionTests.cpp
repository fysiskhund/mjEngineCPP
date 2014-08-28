#include "mjCollisionTests.h"

namespace mjEngine{
mjcolresult mjCollisionTests::SphereVsSphere(mjSphere* s0, mjSphere* s1, mjCollisionResult *out){


	mjVector3 s0ToS1;

	LOGI("in SphvSph; s0 : 0x%x : %3.3f,%3.3f,%3.3f ", s0->c, s0->c->x, s0->c->y, s0->c->z);
	LOGI("in SphvSph; s1 : 0x%x : %3.3f,%3.3f,%3.3f ", s1->c, s1->c->x, s1->c->y, s1->c->z);

	s0ToS1.CopyFrom(*s1->c);

	LOGI("in SphvSph; s0ToS1 : 0x%x : %3.3f,%3.3f,%3.3f ", &s0ToS1, s0ToS1.x, s0ToS1.y, s0ToS1.z);
	s0ToS1.Subtract(*s0->c);

	LOGI("in SphvSph; s0ToS1 : 0x%x : %3.3f,%3.3f,%3.3f ", &s0ToS1, s0ToS1.x, s0ToS1.y, s0ToS1.z);


	float dist = s0ToS1.Normalize();
	LOGI("after Normalise");
	float rSum = s0->r+s1->r;

	LOGI("dist %3.3f, rSum %3.3f", dist, rSum);
	if (dist < rSum)
	{

		if (out != NULL)
		{

			float distHalf = 0.5*dist;

			LOGI("disthalf = %3.3f", distHalf);
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
		LOGI("Returning OVERLAP");
		return MJ_OVERLAP;
	} else
	{
		LOGI("Returning NOCOLLISION, d:%3.3f", dist);
		return MJ_NO_COLLISION;
	}

}
}
