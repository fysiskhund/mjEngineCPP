#ifndef MJANIMATION_H
#define MJANIMATION_H

namespace mjEngine{

#include <vector>
#include "mjAnimationSegment.h"

class mjAnimation
{
    public:

        std::vector<mjAnimationSegment* > segments;

        mjAnimation();
        virtual ~mjAnimation();
    protected:
    private:
};


}
#endif // MJANIMATION_H
