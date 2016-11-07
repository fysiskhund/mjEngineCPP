#ifndef MJGRAPHICTEXT_H
#define MJGRAPHICTEXT_H

#include <string>
#include <vector>
#include "../extLibs/utf8-utils/utf8-utils.h"
#include "../util/mjResourceManager.h"
#include "../util/mjFontResource.h"
#include "mjGraphicCharObject.h"
#include <string.h>




namespace mjEngine {

class mjGraphicText
{
public:

    //bool enableDepthTesting = false; // textShaders will default to NO depth testing, meaning the text is always visible.
    std::vector<mjGraphicCharObject*> textVector;
    std::string text;
    int usedLength = 0;
    mjGraphicText(mjResourceManager* resourceManager, const char* text, const char* font,
                  int fontSize, float renderScale, float positionScale, float* color, mjVector3& position);
    mjVector3 pos;

    char* GetNextChar();    
    void SetRenderScale(float scale);
    void SetPositionScale(float scale);
    void SetColor(float* color);
    void Update(const char* text);

private:


    float color[4] = {1, 1, 1, 1};
    int fontSize;
    float positionScale;
    float renderScale;
    mjFontResource* fontResource;
    mjResourceManager* resourceManager;
};

}
#endif // MJGRAPHICTEXT_H
