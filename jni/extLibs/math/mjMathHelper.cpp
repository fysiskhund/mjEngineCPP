#include "mjMathHelper.h"

namespace mjEngine{


float mjMathHelper::Sign(float x)
{
	if (x > 0)
	{
		return 1.0f;
	} else if (x < 0)
	{
		return -1.0f;
	} else
	{
		return 0.0f;
	}
	/*float res = (x > 0)? 1.0f:(x== 0)? 0.0f: -1.0f;
	//LOGI("Sign(%3.3f) -> %d", x, res);
	return res;*/
}
void mjMathHelper::GetForwardAndLeftDirections(mjVector3& cameraDirection, mjVector3& gravity, mjVector3* outForwardDirection, mjVector3* outLeftDirection)
{

	// Gravity will be the inverse of the normal direction to the imaginary plane in which the forward and left directions must be contained.
	// Which means it needs to either be multiplied by -1

	mjVector3 invGravity;
	invGravity.CopyFrom(gravity);
	invGravity.MulScalar(-1);
	invGravity.Normalize();

	cameraDirection.Normalize();

	// Get the scalar component of camera dir over the gravity direction (both directions are unitary)
	float scalarComponent = cameraDirection.Dot(invGravity);

	// Subtract the vector component of gravity from the camera direction

	outForwardDirection->CopyFrom(cameraDirection);
	outForwardDirection->ScaleSubtract(scalarComponent, invGravity);
	outForwardDirection->Normalize();

	invGravity.CrossOut(*outForwardDirection, outLeftDirection);
	outLeftDirection->Normalize();
	//LOGI("gravity: %3.3f, %3.3f, %3.3f", gravity.x, gravity.y , gravity.z);
	//LOGI("forwardDir: %3.3f, %3.3f, %3.3f", outForwardDirection->x, outForwardDirection->y, outForwardDirection->z);

	//LOGI("leftDir: %3.3f, %3.3f, %3.3f", outLeftDirection->x, outLeftDirection->y, outLeftDirection->z);
}
float mjMathHelper::Rand01f()
{
    return ((float)rand())/((float)RAND_MAX);
}

}
