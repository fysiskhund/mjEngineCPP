#ifndef MJFONTRESOURCE_H
#define MJFONTRESOURCE_H


#include <ft2build.h>
#include FT_FREETYPE_H


#include "mjResource.h"
#include "mjFileFromArchive.h"


namespace mjEngine{

class mjFontResource : public mjResource
{
public:
    FT_Face face;
    mjFileFromArchive* fontFile = NULL;
    mjFontResource();


};

}

#endif // MJFONTRESOURCE_H
