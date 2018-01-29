#include "mj1stPersonCamera.h"

namespace mjEngine {

mj1stPersonCamera::mj1stPersonCamera()
    : mjCamera()
{

}

mj1stPersonCamera::mj1stPersonCamera(mjObject* carryingObject, mjVector3& carryingObjectOffset)
    : mjCamera()
{
    this->dolly = carryingObject;
    this->dollyOffset = carryingObjectOffset;
}

void mj1stPersonCamera::Update(double t_elapsed)
{
    mjCamera::Update(t_elapsed);
    if (this->dolly)
    {
        this->dir.CopyFrom(dolly->dir);
        this->up.CopyFrom(dolly->up);
    }
}

}
