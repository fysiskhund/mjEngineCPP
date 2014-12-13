#ifndef MJANIMATION_H
#define MJANIMATION_H


#include <vector>
#include "mjAnimationSegment.h"

namespace mjEngine{


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
