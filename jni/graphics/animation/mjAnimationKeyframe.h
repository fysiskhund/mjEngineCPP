#ifndef MJANIMATIONKEYFRAME_H
#define MJANIMATIONKEYFRAME_H

#include <string>
#include "../../core/mjVector3.h"

namespace mjEngine{

enum keyframeAnimType { KEYFRAMETYPE_LINEAR=0, KEYFRAMETYPE_QUADRATIC, KEYFRAMETYPE_IGNORE};

class mjAnimationKeyframe
{
    public:

        float timeStamp;

        mjVector3 angles;
        mjVector3 rotationDirections;
        mjVector3 pos;

        keyframeAnimType rotationAnimTypes[3];
        keyframeAnimType displacementAnimTypes[3];

        mjAnimationKeyframe();
        virtual ~mjAnimationKeyframe();
    protected:
    private:
};

}
#endif // MJANIMATIONKEYFRAME_H
