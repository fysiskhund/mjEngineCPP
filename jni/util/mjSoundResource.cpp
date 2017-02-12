#include "mjSoundResource.h"

namespace mjEngine{

mjSoundResource::mjSoundResource()
{
    //ctor
}

mjSoundResource::~mjSoundResource()
{
#if !defined(ANDROID_ASSMAN) && !defined(IOS)
    // The buffer is NOT soundResource's responsibility and should be freed by the app before calling this destructor
    if (memRWop)
    {
        SDL_free(memRWop);
    }
#endif
}

}
