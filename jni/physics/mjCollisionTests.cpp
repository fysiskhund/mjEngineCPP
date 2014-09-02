#include "mjCollisionTests.h"

namespace mjEngine{
mjcolresult mjCollisionTests::SphereVsSphere(mjSphere* s0, mjSphere* s1, mjCollisionResult *out){


	mjVector3 s0ToS1;

	//LOGI("in SphvSph; s0 : 0x%x : %3.3f,%3.3f,%3.3f ", s0->c, s0->c->x, s0->c->y, s0->c->z);
	//LOGI("in SphvSph; s1 : 0x%x : %3.3f,%3.3f,%3.3f ", s1->c, s1->c->x, s1->c->y, s1->c->z);

	s0ToS1.CopyFrom(*s1->c);

	//LOGI("in SphvSph; s0ToS1 : 0x%x : %3.3f,%3.3f,%3.3f ", &s0ToS1, s0ToS1.x, s0ToS1.y, s0ToS1.z);
	s0ToS1.Subtract(*s0->c);

	//LOGI("in SphvSph; s0ToS1 : 0x%x : %3.3f,%3.3f,%3.3f ", &s0ToS1, s0ToS1.x, s0ToS1.y, s0ToS1.z);


	float dist = s0ToS1.Normalize();
	//LOGI("after Normalise");
	float rSum = s0->r+s1->r;

	//LOGI("dist %3.3f, rSum %3.3f", dist, rSum);
	if (dist < rSum)
	{

		if (out != NULL)
		{

			float minDistHalf = rSum*0.5;

			//LOGI("minDistHalf = %3.3f", minDistHalf);
			out->relocationEffectObj0 = new mjPhysicsEffect();
			out->relocationEffectObj0->type = MJ_COLLISION;
			out->relocationEffectObj0->action = MJ_CHANGE_POSITION;

			s0ToS1.MulScalar(-minDistHalf);

			out->relocationEffectObj0->value.CopyFrom(s0ToS1);




			out->relocationEffectObj1 = new mjPhysicsEffect();
			out->relocationEffectObj1->type = MJ_COLLISION;
			out->relocationEffectObj1->action = MJ_CHANGE_POSITION;

			s0ToS1.MulScalar(-1);

			out->relocationEffectObj1->value.CopyFrom(s0ToS1);
			out->result= MJ_OVERLAP;

		}
		//LOGI("Returning OVERLAP");
		return MJ_OVERLAP;
	} else
	{
		//LOGI("Returning NOCOLLISION, d:%3.3f", dist);
		return MJ_NO_COLLISION;
	}

}



mjcolresult mjCollisionTests::AABBVsAABB(mjAABB* aabb0, mjAABB* aabb1, mjCollisionResult* out)
	{

		if ((aabb0->minCorner.x > aabb1->maxCorner.x) || (aabb0->minCorner.y > aabb1->maxCorner.y) || (aabb0->minCorner.z > aabb1->maxCorner.z) ||
		    (aabb1->minCorner.x > aabb0->maxCorner.x) || (aabb1->minCorner.y > aabb0->maxCorner.y) || (aabb1->minCorner.z > aabb0->maxCorner.z))
		{
			/*LOGI("[%3.3f, %3.3f, %3.3f ; %3.3f, %3.3f, %3.3f] vs [%3.3f, %3.3f, %3.3f ; %3.3f, %3.3f, %3.3f]",
					aabb0->minCorner.x, aabb0->minCorner.y, aabb0->minCorner.z,
					aabb0->maxCorner.x, aabb0->maxCorner.y, aabb0->maxCorner.z,

					aabb1->minCorner.x, aabb1->minCorner.y, aabb1->minCorner.z,
					aabb1->maxCorner.x, aabb1->maxCorner.y, aabb1->maxCorner.z);

			LOGI("%d %d %d\n%d %d %d",
					 (aabb0->minCorner.x > aabb1->maxCorner.x),
					 (aabb0->minCorner.y > aabb1->maxCorner.y),
					 (aabb0->minCorner.z > aabb1->maxCorner.z),

					 (aabb1->minCorner.x > aabb0->maxCorner.x),
					 (aabb1->minCorner.y > aabb0->maxCorner.y),
					 (aabb1->minCorner.z > aabb0->maxCorner.z)
					 );*/
			//LOGI("No collision AABB");
			return MJ_NO_COLLISION;
		} else
		{
			//LOGI("COLLISION!!AABB");
			mjcolresult result = MJ_OVERLAP;

			if (out != NULL)
			{
				/*out->relocationEffectObj0 = new mjPhysicsEffect();
				out->relocationEffectObj1 = new mjPhysicsEffect();*/
				// Get the directions for moving the boxes
				mjVector3 directions;
				directions.CopyFrom(*aabb0->center);
				directions.Subtract(*aabb1->center);

				mjVector3 maxEndp;
				maxEndp.Set(fmin(aabb0->maxCorner.x, aabb1->maxCorner.x), fmin(aabb0->maxCorner.y, aabb1->maxCorner.y),
							fmin(aabb0->maxCorner.z, aabb1->maxCorner.z));
				mjVector3 minEndp;
				minEndp.Set(fmax(aabb0->minCorner.x, aabb1->minCorner.x), fmax(aabb0->minCorner.y, aabb1->minCorner.y),
						fmax(aabb0->minCorner.z, aabb1->minCorner.z));

				mjVector3 overlap;
				overlap.CopyFrom(maxEndp);
				overlap.Subtract(minEndp);


				out->relocationEffectObj0 = new mjPhysicsEffect(MJ_COLLISION, MJ_CHANGE_POSITION);
				out->changeVelEffectObj0 = new mjPhysicsEffect(MJ_COLLISION, MJ_ADD_VELOCITY);

				out->relocationEffectObj1 = new mjPhysicsEffect(MJ_COLLISION, MJ_CHANGE_POSITION);
				out->changeVelEffectObj1 = new mjPhysicsEffect(MJ_COLLISION, MJ_ADD_VELOCITY);



				mjVector3* location0 = &out->relocationEffectObj0->value;
				mjVector3* location1 = &out->relocationEffectObj1->value;

				float displacementFactor = 0.5f;

				if (aabb0->isImmovable || aabb1->isImmovable)
				{
					displacementFactor = 1;
				}

				if ((overlap.x < overlap.y) && (overlap.x < overlap.z))
				{
					location0->x = aabb1->center->x + (mjMathHelper::Sign(directions.x)*(aabb0->halfWidths.x + aabb1->halfWidths.x)*displacementFactor);
					location1->x = aabb0->center->x - (mjMathHelper::Sign(directions.x)*(aabb0->halfWidths.x + aabb1->halfWidths.x)*displacementFactor);

					out->changeVelEffectObj0->value.Set(mjMathHelper::Sign(directions.x), 0, 0);
					out->changeVelEffectObj1->value.Set(-mjMathHelper::Sign(directions.x), 0, 0);

					out->relocationEffectObj0->mask[1] = false;
					out->relocationEffectObj0->mask[2] = false;
					out->changeVelEffectObj0->mask[1] = false;
					out->changeVelEffectObj0->mask[2] = false;

					out->relocationEffectObj1->mask[1] = false;
					out->relocationEffectObj1->mask[2] = false;
					out->changeVelEffectObj1->mask[1] = false;
					out->changeVelEffectObj1->mask[2] = false;
				} else if ((overlap.y < overlap.x ) && (overlap.y < overlap.z))
				{
					location0->y = aabb1->center->y + (mjMathHelper::Sign(directions.y)*(aabb0->halfWidths.y + aabb1->halfWidths.y)*displacementFactor);
					location1->y = aabb0->center->y - (mjMathHelper::Sign(directions.y)*(aabb0->halfWidths.y + aabb1->halfWidths.y)*displacementFactor);

					out->changeVelEffectObj0->value.Set(0, mjMathHelper::Sign(directions.y), 0);
					out->changeVelEffectObj1->value.Set(0, -mjMathHelper::Sign(directions.y), 0);


					out->relocationEffectObj0->mask[0] = false;
					out->relocationEffectObj0->mask[2] = false;
					out->changeVelEffectObj0->mask[0] = false;
					out->changeVelEffectObj0->mask[2] = false;

					out->relocationEffectObj1->mask[0] = false;
					out->relocationEffectObj1->mask[2] = false;
					out->changeVelEffectObj1->mask[0] = false;
					out->changeVelEffectObj1->mask[2] = false;
				} else
				{
					location0->z = aabb1->center->z + (mjMathHelper::Sign(directions.z)*(aabb0->halfWidths.z + aabb1->halfWidths.z)*displacementFactor);
					location1->z = aabb0->center->z - (mjMathHelper::Sign(directions.z)*(aabb0->halfWidths.z + aabb1->halfWidths.z)*displacementFactor);

					out->changeVelEffectObj0->value.Set(0, 0, mjMathHelper::Sign(directions.z));
					out->changeVelEffectObj1->value.Set(0, 0, -mjMathHelper::Sign(directions.z));

					out->relocationEffectObj0->mask[0] = false;
					out->relocationEffectObj0->mask[1] = false;
					out->changeVelEffectObj0->mask[0] = false;
					out->changeVelEffectObj0->mask[1] = false;

					out->relocationEffectObj1->mask[0] = false;
					out->relocationEffectObj1->mask[1] = false;
					out->changeVelEffectObj1->mask[0] = false;
					out->changeVelEffectObj1->mask[1] = false;
				}
				LOGI("displacement obj0: %3.3f, %3.3f, %3.3f",
						out->relocationEffectObj0->value.x,
						out->relocationEffectObj0->value.y,
						out->relocationEffectObj0->value.z
						);


			}

			return result;
		}


	}
}
