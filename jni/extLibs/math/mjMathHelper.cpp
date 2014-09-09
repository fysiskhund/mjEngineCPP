#include "mjMathHelper.h"

namespace mjEngine{


float mjMathHelper::Sign(float x)
{
	int res = (x > 0)? 1:(x== 0)? 0: -1;
	//LOGI("Sign(%3.3f) -> %d", x, res);
	return res;
}
void mjMathHelper::GetForwardAndLeftDirections(mjVector3& cameraDirection, mjVector3& gravity, mjVector3* outForwardDirection, mjVector3* outLeftDirection)
{

	// Get the scalar component of camera dir over the gravity direction (both directions are unitary)
	float scalarComponent = cameraDirection.Dot(gravity);

	// Subtract the vector component of gravity from the camera direction

	outForwardDirection->CopyFrom(cameraDirection);
	outForwardDirection->ScaleSubtract(scalarComponent, gravity);
	outForwardDirection->Normalize();

	outForwardDirection->CrossOut(gravity, outLeftDirection);
	outLeftDirection->Normalize();
	LOGI("gravity: %3.3f, %3.3f, %3.3f", gravity.x, gravity.y , gravity.z);
	LOGI("forwardDir: %3.3f, %3.3f, %3.3f", outForwardDirection->x, outForwardDirection->y, outForwardDirection->z);

	LOGI("leftDir: %3.3f, %3.3f, %3.3f", outLeftDirection->x, outLeftDirection->y, outLeftDirection->z);
}

}
