#ifndef MJMODELPOSE_H
#define MJMODELPOSE_H

#include <vector>

#include "../../core/mjVector3.h"

namespace mjEngine{

class mjModelPose
{
    public:
        mjModelPose();
        std::vector<mjVector3*> positions;
        std::vector<mjVector3*> angles;
        ~mjModelPose();
    protected:
    private:
};

}

#endif // MJMODELPOSE_H
