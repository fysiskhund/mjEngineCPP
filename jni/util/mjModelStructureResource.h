#ifndef MJMODELSTRUCTURERESOURCE_H
#define MJMODELSTRUCTURERESOURCE_H

#include "mjResource.h"
#include "../graphics/animation/mjModelStructure.h"

namespace mjEngine{

class mjModelStructureResource: public mjResource
{
    public:
        mjModelStructure* structure;
        virtual ~mjModelStructureResource();
    protected:
    private:
};

}
#endif // MJMODELSTRUCTURERESOURCE_H
