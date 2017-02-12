#include "mjFileFromArchive.h"


namespace mjEngine {

mjFileFromArchive::mjFileFromArchive()
{
    LOGI("New mjFileFromArchive");
}

mjFileFromArchive::~mjFileFromArchive()
{
#ifdef ANDROID_ASSMAN
    // Nothing!
#else

    // Delete the buffer contents if present.
    if (internalUseOnly_wholeFileBuffer)
    {
        delete [] internalUseOnly_wholeFileBuffer;
    }
    fclose(internalUseOnly_fileDescriptor);
#endif
}

}
