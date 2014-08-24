#include "mjCamera.h"

namespace mjEngine{

mjCamera::mjCamera()
{
	pos.Set(0,0,0);
	dir.Set(0,0,-1);
	up.Set(0,1,0);

}
void mjCamera::GetLookAtMatrix(float* m)
{
	Matrix4::SetLookAtM(m, 0, pos, dir, up);
	/*mjVector3 center3Dv(pos);

	center3Dv.Add(dir);

	float eyePosition3D[3];
	pos.CopyToArray(eyePosition3D);

	float center3D[3];
	center3Dv.CopyToArray(center3D);

	float upVector3D[3];
	up.CopyToArray(upVector3D);

	Matrix4::glhLookAtf2( m, eyePosition3D,
            center3D, upVector3D );*/
}

}
