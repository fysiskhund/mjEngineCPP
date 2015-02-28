#ifndef MJSOUNDRESOURCE_H
#define MJSOUNDRESOURCE_H

#include "mjResource.h"

namespace mjEngine{

class mjSoundResource: public mjResource
{
    public:

		int soundIndexAndroid;
        mjSoundResource();
        virtual ~mjSoundResource();
    protected:
    private:
};

}

#endif // MJSOUNDRESOURCE_H
