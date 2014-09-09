#include "mj3rdPersonCamera.h"

namespace mjEngine{

#define MJ_3_2_PI 4.712388
#define MJ_1_2_PI 1.570796

void mj3rdPersonCamera::SetTarget(mjVector3* target, mjVector3& offset)
{
	this->target = target;
	this->offset.CopyFrom(offset);

}
void mj3rdPersonCamera::Update(float t_elapsed)
{
	if (target)
	{
		mjVector3 targetPlusOffset;
		targetPlusOffset.CopyFrom(*target);
		targetPlusOffset.Add(offset);


		mjVector3 angleOffset;

		angleOffset.x = sin(theta + MJ_1_2_PI)*sin(phi);
		angleOffset.y = cos(theta + MJ_1_2_PI);
		angleOffset.z = sin(theta + MJ_1_2_PI)*cos(phi);

		dir.CopyFrom(angleOffset);
		dir.MulScalar(-1);

		pos.CopyFrom(targetPlusOffset);
		pos.ScaleAdd(r, angleOffset);

		//LOGI("CameraDirFromAngleOffset %3.3f, %3.3f, %3.3f", dir.x, dir.y, dir.z);
	}
}

}
