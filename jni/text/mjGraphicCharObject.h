#ifndef MJGRAPHICCHAROBJECT_H
#define MJGRAPHICCHAROBJECT_H

#include "../core/mjObject.h"
#include "../extLibs/utf8-utils/utf8-utils.h"

namespace mjEngine {


class mjGraphicCharObject : public mjObject
{
public:
    mjFontResource* fontResource;
    unsigned long charToRenderLong;
    int fontSize;
    float charRatio;
    float charOffsetX;
    float charOffsetY;
    float nextCharOffsetX;

    mjGraphicCharObject(mjResourceManager* resourceManager, mjFontResource* fontResource,
                        int fontSize, unsigned long charToRenderLong, float renderScale, float positionScale);
private:
    void GenerateTexture();

};

}
#endif // MJGRAPHICCHAROBJECT_H
