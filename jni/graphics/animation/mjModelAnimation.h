#ifndef MJMODELANIMATION_H
#define MJMODELANIMATION_H

#include "mjModelPose.h"

namespace mjEngine{

class mjModelAnimation
{
    public:
        mjModelAnimation();
        void Update(double t_elapsed, mjModelPose* pose, int state);
        ~mjModelAnimation();
    protected:
    private:
};

}

#endif // MJMODELANIMATION_H
