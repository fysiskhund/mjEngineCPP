#ifndef MJMODELRESOURCE_H
#define MJMODELRESOURCE_H

#include <string>

#include "../graphics/mjModel.h"
#include "mjResource.h"

namespace mjEngine {


class mjModelResource: public mjResource
{
    public:
        mjModel* model;
    protected:
    private:
};

}

#endif // MJMODELRESOURCE_H
