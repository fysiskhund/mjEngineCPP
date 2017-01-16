#ifndef MJGRAPHICTEXT_H
#define MJGRAPHICTEXT_H

#include <string>
#include <vector>
#include "../core/mjObject.h"
#include "../extLibs/utf8-utils/utf8-utils.h"
#include "../util/mjResourceManager.h"
#include "../util/mjFontResource.h"
#include "mjGraphicCharObject.h"

#include <string.h>




namespace mjEngine {

enum TextAlignment {ALIGNMENT_LEFT, ALIGNMENT_CENTER, ALIGNMENT_RIGHT};

class mjGraphicText: public mjObject
{
public:

    //bool enableDepthTesting = false; // textShaders will default to NO depth testing, meaning the text is always visible.
    //std::vector<mjGraphicCharObject*> textVector;
    std::string text;
    int usedLength = 0;
    mjGraphicText(mjResourceManager* resourceManager, const char* text, const char* font,
                  int fontSize, float renderScale, float positionScaleHz, float positionScaleVr,
                  float* color, mjVector3& position, TextAlignment alignment = ALIGNMENT_LEFT);

    float modelMatrix[16];



    float totalWidth = 0;

    void SetRenderScale(float scale);
    void SetPositionScale(float positionScaleHz);
    void SetColor(float* color);
    void UpdateModelMatrix();
    void Update(const char* format, ...);

private:


    TextAlignment alignment = ALIGNMENT_LEFT;
    float color[4] = {1, 1, 1, 1};
    int fontSize;
    float positionScaleHz;
    float positionScaleVr;
    float renderScale;
    mjFontResource* fontResource;
    mjResourceManager* resourceManager;
    char* GetNextChar();
};

}
#endif // MJGRAPHICTEXT_H
