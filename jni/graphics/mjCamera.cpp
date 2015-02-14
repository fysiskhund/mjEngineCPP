#include "mjCamera.h"

namespace mjEngine{

mjCamera* mjCamera::currentCamera = NULL;

mjCamera::mjCamera()
{
	pos.Set(0,0,0);
	dir.Set(0,0,-1);
	up.Set(0,1,0);

}
void mjCamera::GetLookAtMatrix(float* m)
{
	Matrix4::SetLookAtM(m, 0, pos, dir, up);
}

void mjCamera::SetAsCurrentCamera()
{
    mjCamera::currentCamera = this;
}

}
