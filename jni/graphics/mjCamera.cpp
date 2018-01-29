#include "mjCamera.h"

namespace mjEngine{

mjCamera* mjCamera::currentCamera = NULL;

mjCamera::mjCamera()
    :mjObject(NULL)
{
	pos.Set(0,0,0);
	dir.Set(0,0,-1);
	up.Set(0,1,0);

}

void mjCamera::AttachToObject(mjObject* dolly, mjVector3& dollyOffset)
{
    this->dolly = dolly;
    this->dollyOffset.CopyFrom(dollyOffset);
}

void mjCamera::GetLookAtMatrix(GLfloat* m)
{
	Matrix4::SetLookAtM(m, 0, pos, dir, up);
}

void mjCamera::SetAsCurrentCamera()
{
    mjCamera::currentCamera = this;
}

void mjCamera::Update(double t_elapsed)
{
    if (dolly != nullptr)
    {
        // Immediately acquire the dolly's position and offset it as needed.
        pos.CopyFrom(dolly->pos);
        pos.Add(dollyOffset);
    }
}

}
