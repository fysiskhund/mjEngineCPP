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


    float modelMatrix[16];



    float totalWidth = 0;

    /*!
     * If immediateUpdate is set to true, then it's important to ONLY send updates when
     * there is a GL context available. In Android, events arrive asynchronously, so there is
     * NO GL context available until the main thread (e.g. Update(t_elapsed) runs.
     * When it is set to false, the changes in the text will only be reflected until Update(t_elapsed) runs
     * but then you must remember to call the Update() method!
     */
    bool immediateUpdate = true;

    mjGraphicText(mjResourceManager* resourceManager, const char* text, const char* font,
                  int fontSize, float renderScale, float positionScaleHz, float positionScaleVr,
                  float* color, mjVector3& position, TextAlignment alignment = ALIGNMENT_LEFT);



    void SetRenderScale(float scale);
    void SetPositionScale(float positionScaleHz);
    void SetColor(float* color);
    void UpdateModelMatrix();
    void UpdateText(const char* format, ...);
    void Update(float t_elapsed) override;

    virtual ~mjGraphicText();
private:


    TextAlignment alignment = ALIGNMENT_LEFT;
    float color[4] = {1, 1, 1, 1};
    int fontSize;
    float positionScaleHz;
    float positionScaleVr;
    float renderScale;
    mjFontResource* fontResource;
    mjResourceManager* resourceManager;
    bool requiresTextUpdate = false;
    char* GetNextChar();
    void UpdateTextStatic(const char* text);


    // mjObject interface
public:
    void SetDetailsFromXML(XMLElement* entity) override;

    // mjInternalMessageReceiver interface
public:
    void ReceiveInternalMessage(void* contents, unsigned int type, void* sender) override;
};

}
#endif // MJGRAPHICTEXT_H
