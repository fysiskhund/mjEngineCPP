#ifndef MJGRAPHICCHAROBJECTRESOURCE_H
#define MJGRAPHICCHAROBJECTRESOURCE_H


#include "../extLibs/util/mjMultiPlatform.h"
#include "../extLibs/utf8-utils/utf8-utils.h"
#include "../extLibs/logger/mjLog.h"
#include "mjResource.h"
#include "mjFontResource.h"


#include <ft2build.h>
#include FT_FREETYPE_H

namespace mjEngine {

class mjGraphicCharObjectResource : public mjResource
{
public:

    // Resource object-specific notes:
    // In this case the modifier will say which font and size it is.
    // modifier = (fontResource->identifier) + (fontSize * 100).
    // So there can be only 100 fonts loaded at a time. S'ok.

    // ----


    GLuint texture;


    float charWidth;
    float charHeight;

    float manualRelocation = 0;

    float charRatio;
    float bitmapLeft;
    float bitmapTop;
    float advanceX;
    mjFontResource* fontResource;
    int fontSize;
    unsigned long charToRenderLong;

    mjGraphicCharObjectResource(mjFontResource* fontResource, int fontSize,
                                unsigned long charToRenderLong);




private:
    void GenerateTexture();


};

}
#endif // MJGRAPHICCHAROBJECTRESOURCE_H
