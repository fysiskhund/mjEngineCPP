#ifndef MJFILEFROMARCHIVE_H
#define MJFILEFROMARCHIVE_H

#include "../extLibs/util/mjMultiPlatform.h"
#include "../extLibs/logger/mjLog.h"

#ifdef IOS
#include <string>
#endif

namespace mjEngine {


class mjFileFromArchive
{
public:
    //int ID = -1;
    mjFileFromArchive();
    ~mjFileFromArchive();
#ifdef ANDROID_ASSMAN
        AAsset* ass = NULL;
#else
    unsigned char* internalUseOnly_wholeFileBuffer = NULL;
    size_t internalUseOnly_wholeFileBufferSize = 0;
    FILE* internalUseOnly_fileDescriptor = 0;
#endif
#ifdef IOS
    std::string iosOnly_fullPath;
#endif


};

}
#endif // MJFILEFROMARCHIVE_H
