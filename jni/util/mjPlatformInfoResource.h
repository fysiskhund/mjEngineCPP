#ifndef MJPLATFORMINFORESOURCE_H
#define MJPLATFORMINFORESOURCE_H

#include "mjResource.h"

namespace mjEngine {

enum MJ_PLATFORMTYPE{
    MJ_PTYPE_PC_LINUX,
    MJ_PTYPE_PC_WINDOWS,
    MJ_PTYPE_PC_MACOS,
    MJ_PTYPE_PC_UNKNOWN,

    MJ_PTYPE_ANDROID_PHONE,
    MJ_PTYPE_ANDROID_TABLET,
    MJ_PTYPE_ANDROID_PHABLET,
    MJ_PTYPE_ANDROID_TV,
    MJ_PTYPE_ANDROID_UNKNOWN,

    MJ_PTYPE_IOS_IPHONE,
    MJ_PTYPE_IOS_IPAD,
    MJ_PTYPE_IOS_APPLETV,
    MJ_PTYPE_IOS_UNKNOWN,

    MJ_PTYPE_UNKNOWN
};

enum MJ_SCREENSIZE{
    MJ_SCREENSIZE_UNKNOWN,
    MJ_SCREENSIZE_XXS,
    MJ_SCREENSIZE_XS,
    MJ_SCREENSIZE_S,
    MJ_SCREENSIZE_M,
    MJ_SCREENSIZE_L,
    MJ_SCREENSIZE_XL,
    MJ_SCREENSIZE_XXL
};

class mjPlatformInfoResource : public mjResource
{
public:
    MJ_PLATFORMTYPE platformType = MJ_PTYPE_UNKNOWN;

    MJ_SCREENSIZE screenSize = MJ_SCREENSIZE_UNKNOWN;

    float deviceHeight_cm = -1;
    float deviceWidth_cm = -1;

    int deviceWidth_px = -1;
    int deviceHeight_px = -1;

    float ppi_x = -1;
    float ppi_y = -1;


    mjPlatformInfoResource();
};

}
#endif // MJPLATFORMINFORESOURCE_H
