#ifndef MJTEXTURERESOURCE_H
#define MJTEXTURERESOURCE_H

#include "../extLibs/util/mjMultiPlatform.h"

#include "mjResource.h"
#include "mjFileFromArchive.h"

namespace mjEngine {

class mjTextureResource: public mjResource
{
    public:

        GLuint glResourceID;

        mjFileFromArchive* mjFile = NULL;

    protected:
    private:
};

}
#endif // MJTEXTURERESOURCE_H
