#ifndef MJANIMATOR_H
#define MJANIMATOR_H

#include "mjModelPose.h"
#include "mjAnimation.h"

namespace mjEngine{

class mjAnimator
{
    public:
        float t;

        mjAnimator();
        virtual ~mjAnimator();

        void UpdatePose(float t, mjModelPose& pose, mjAnimation& animation);

    protected:
    private:
};

}
#endif // MJANIMATOR_H
