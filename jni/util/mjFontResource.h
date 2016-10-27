#ifndef MJFONTRESOURCE_H
#define MJFONTRESOURCE_H


#include <ft2build.h>
#include FT_FREETYPE_H


#include "mjResource.h"


namespace mjEngine{

class mjFontResource : public mjResource
{
public:
    mjFontResource();

    FT_Face face;
};

}

#endif // MJFONTRESOURCE_H
