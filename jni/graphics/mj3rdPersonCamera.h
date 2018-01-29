#ifndef MJ3RDPERSONCAMERA_H
#define MJ3RDPERSONCAMERA_H

#include "../extLibs/util/mjMultiPlatform.h"

#include "mjCamera.h"



namespace mjEngine{

class mj3rdPersonCamera: public mjCamera{
public:
    //! Default constructor. Not recommended as target is still absolutely necessary for the camera to operate
    mj3rdPersonCamera();

    //! Construct and set a target. The target can be a reference to the position of the player's avatar for example
    mj3rdPersonCamera(mjVector3* target);

    //! Construct the camera and set a target, and an offset. The camera uses (target + offset) as the position being tracked
    mj3rdPersonCamera(mjVector3 *target, mjVector3& offset);

    //! Set the target and the offset. The camera uses (target + offset) as the position being tracked
    void SetTarget(mjVector3* target, mjVector3& offset);

    //! Track the target.
    virtual void Update(double t_elapsed) override;

    GLfloat theta = 0;
    GLfloat phi   = 0;
    GLfloat r     = 4;

private:
    mjVector3* target = nullptr;
    mjVector3 offset;

};

}


#endif
