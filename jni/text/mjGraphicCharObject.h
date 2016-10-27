#ifndef MJGRAPHICCHAROBJECT_H
#define MJGRAPHICCHAROBJECT_H

#include "../core/mjObject.h"
#include "../extLibs/utf8-utils/utf8-utils.h"

namespace mjEngine {


class mjGraphicCharObject : public mjObject
{
public:
    mjFontResource* fontResource;
    char* charToRender;
    unsigned long charToRenderFT;
    int fontSize;
    mjGraphicCharObject(mjResourceManager* resourceManager, mjFontResource* fontResource, int fontSize, char* charToRender);
private:
    void GenerateTexture();

};

}
#endif // MJGRAPHICCHAROBJECT_H
