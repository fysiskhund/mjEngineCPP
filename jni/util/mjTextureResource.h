#ifndef MJTEXTURERESOURCE_H
#define MJTEXTURERESOURCE_H

#include "../extLibs/util/mjMultiPlatform.h"

#include "mjResource.h"

namespace mjEngine {

class mjTextureResource: public mjResource
{
    public:

        GLuint glResourceID;
    protected:
    private:
};

}
#endif // MJTEXTURERESOURCE_H
