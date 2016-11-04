#include "mjGraphicText.h"

namespace mjEngine {


mjGraphicText::mjGraphicText(mjResourceManager* resourceManager, const char* text, const char* font, int fontSize, float renderScale, float positionScale)
{
    this->text = text;
    // Determine how many chars we're going to render
    int totalLength = strnlen(text, 1024);

    int pos = 0;

    std::string fontPath = font;

    mjFontResource* fontResource = resourceManager->FetchFont(fontPath);

    while (pos < totalLength)
    {
        int thisCharLength = ftgl::utf8_surrogate_len(&text[pos]);

        if (!thisCharLength)
        {
            LOGI("mjGraphicText: Invalid char in %s [%d]!", text, pos);
            break;
        } else
        {
            char charCharCharmander[5];
            for (int j = 0; j < 5; j++)
            {
                if (j < thisCharLength)
                {
                    charCharCharmander[j] = text[pos + j];
                } else
                {
                    charCharCharmander[j] = 0;
                    break;
                }
            }
            LOGI(" ****** ");

            LOGI("Char: %s", charCharCharmander);
        }
        unsigned long thisCharLong = ftgl::utf8_to_utf32(&(text[pos]));
        //LOGI("Char: (%lu) %s", thisCharLong, &(text[pos]));


        mjGraphicCharObject* charObject = new mjGraphicCharObject(resourceManager, fontResource, fontSize, thisCharLong, renderScale);
        if (charObject->charRatio > 4)
        {

            charObject->manualRelocation = -charObject->charWidth; //FIXME: Why is this necessary??
        }
        LOGI("width: %d, bitmapLeft: %f, advance: %f", charObject->charWidth, charObject->bitmapLeft, (charObject->advanceX/64.0) );
        textVector.push_back(charObject);
        pos += thisCharLength;
    }
    SetPositionScale(positionScale);
    SetRenderScale(renderScale);

    LOGI("End of creating text.");
}

void mjGraphicText::SetRenderScale(float renderScale)
{
    this->renderScale = renderScale;
    for (int i = 0; i < textVector.size(); i++)
    {
        textVector[i]->scale.Set(textVector[i]->charWidth*renderScale, textVector[i]->charHeight*renderScale, 1);
    }
}

void mjGraphicText::SetPositionScale(float positionScale)
{

    this->positionScale = positionScale;
    float displacement = 0;

    for (int i = 0; i < textVector.size(); i++)
    {
        textVector[i]->pos.y = (textVector[i]->bitmapTop - textVector[i]->charHeight)*0.003; //FIXME: is this value fixed forever?
        textVector[i]->pos.x = (displacement + textVector[i]->bitmapLeft + textVector[i]->manualRelocation)*positionScale;
        displacement +=  (textVector[i]->advanceX/64.0);
    }
}

void mjGraphicText::Update(const char *text)
{
    this->text;

}


}
