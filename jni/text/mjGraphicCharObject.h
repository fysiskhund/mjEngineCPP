#ifndef MJGRAPHICCHAROBJECT_H
#define MJGRAPHICCHAROBJECT_H

#include "../util/mjResourceManager.h"
#include "../util/mjGraphicCharObjectResource.h"
#include "../core/mjObject.h"
#include "../extLibs/utf8-utils/utf8-utils.h"


namespace mjEngine {


class mjGraphicCharObject : public mjObject
{
public:
    mjFontResource* fontResource;
    unsigned long charToRenderLong;
    float renderScale;

    int fontSize;

    float charWidth;
    float charHeight;

    //float manualRelocation = 0;

    float charRatio;
    float bitmapLeft;
    float bitmapTop;
    int advanceX;




    mjGraphicCharObject(mjResourceManager* resourceManager, mjFontResource* fontResource,
                        int fontSize, unsigned long charToRenderLong, float renderScale);
    void SetGraphicCharResource(mjGraphicCharObjectResource* resource);
    virtual ~mjGraphicCharObject();
private:

    mjGraphicCharObjectResource* graphicCharObjectResource;
};

}
#endif // MJGRAPHICCHAROBJECT_H
