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


    std::vector<mjGraphicCharObject*> textVector;
    std::string text;
    mjGraphicText(mjResourceManager* resourceManager, const char* text, const char* font, int fontSize, float renderScale, float positionScale);
    char* GetNextChar();
    void SetRenderScale(float scale);
    void SetPositionScale(float scale);
    void Update(const char* text);
private:
    float positionScale;
    float renderScale;
};

}
#endif // MJGRAPHICTEXT_H
