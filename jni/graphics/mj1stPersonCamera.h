#ifndef MJ1STPERSONCAMERA_H
#define MJ1STPERSONCAMERA_H

#include "../extLibs/util/mjMultiPlatform.h"

#include "mjCamera.h"


namespace mjEngine {


class mj1stPersonCamera : public mjCamera
{
public:
    mjObject* carryingObject = nullptr;
    //! Not recommended because the carrying object is necessary for the camera's operation
    mj1stPersonCamera();

    //! Initialise with the carryingObject, which would be the "1st person", and an offset since potentially
    //! you want the camera to be on their head instead of the pelvis or feet or whatever the object's insertion point is
    mj1stPersonCamera(mjObject* carryingObject, mjVector3& carryingObjectOffset);

    // mjObject interface
public:
    virtual void Update(double t_elapsed) override;
};

}
#endif // MJ1STPERSONCAMERA_H
