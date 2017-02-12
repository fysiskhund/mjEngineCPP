#ifndef MJSOUNDRESOURCE_H
#define MJSOUNDRESOURCE_H

#include "mjResource.h"
#include "mjFileFromArchive.h"

namespace mjEngine{

class mjSoundResource: public mjResource
{
    public:

		int soundIndexAndroid;

        mjFileFromArchive* fileFromArchive = NULL; // Note: not valid on Android!
        const unsigned char* buffer = NULL; // Note: not valid on Android!
        size_t bufferSize = 0; // Note: not valid on Android!

#if !defined(ANDROID_ASSMAN) && !defined(IOS)

        SDL_RWops* memRWop = NULL;
#endif

        mjSoundResource();
        virtual ~mjSoundResource();
    protected:
    private:
};

}

#endif // MJSOUNDRESOURCE_H
