#ifndef MJANIMATIONKEYFRAME_H
#define MJANIMATIONKEYFRAME_H

#include <string>
#include "../../core/mjVector3.h"

namespace mjEngine{

class mjAnimationKeyframe
{
    public:

        mjVector3 angles;
        mjVector3 rotationDirections;
        mjVector3 pos;

        mjAnimationKeyframe();
        virtual ~mjAnimationKeyframe();
    protected:
    private:
};

}
#endif // MJANIMATIONKEYFRAME_H
