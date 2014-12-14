#ifndef MJMODELSTRUCTURERESOURCE_H
#define MJMODELSTRUCTURERESOURCE_H

#include "mjResource.h"
#include "../graphics/animation/mjModelStructure.h"

namespace mjEngine{

class mjModelStructureResource: public mjResource
{
    public:
        mjModelStructure* structure;
        mjModelStructureResource();
        virtual ~mjModelStructureResource();
    protected:
    private:
};

}
#endif // MJMODELSTRUCTURERESOURCE_H
