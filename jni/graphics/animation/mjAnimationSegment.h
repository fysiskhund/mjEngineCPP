#ifndef MJANIMATIONSEGMENT_H
#define MJANIMATIONSEGMENT_H

#include <string>
#include <vector>

#include "mjAnimationKeyframe.h"

namespace mjEngine{

class mjAnimationSegment
{
    public:
        std::string meshName;
        std::vector<mjAnimationKeyframe *> keyframes;
        int meshNum;
        float totalTime;

        mjAnimationSegment();
        virtual ~mjAnimationSegment();
    protected:
    private:
};

}

#endif // MJANIMATIONSEGMENT_H
