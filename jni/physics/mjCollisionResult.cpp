#include "mjCollisionResult.h"

namespace mjEngine{

void mjCollisionResult::Reset()
{
    // The fields are assumed to be clean if the result is "no collision"
    // So they are only actually reset if necessary
    if (result != MJ_NO_COLLISION)
    {
        result = MJ_NO_COLLISION;

        changeVelEffectObj0.Reset();
        changeVelEffectObj1.Reset();
        relocationEffectObj0.Reset();
        relocationEffectObj1.Reset();
        accelObj0.Reset();
        accelObj1.Reset();
    }
}



}
