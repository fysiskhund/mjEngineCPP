#include "mjGraphicText.h"

namespace mjEngine {


mjGraphicText::mjGraphicText(mjResourceManager* resourceManager, const char* text, const char* font, int fontSize,
                             float renderScale, float positionScale, float* color, mjVector3& position)
{
    this->text = text;
    this->resourceManager = resourceManager;
    this->fontSize = fontSize;
    this->renderScale = renderScale;
    this->positionScale = positionScale;
    this->pos.CopyFrom(position);
    // Determine how many chars we're going to render




    std::string fontPath = font;

    fontResource = resourceManager->FetchFont(fontPath);

    for (int j = 0; j < 4; j++)
    {
        this->color[j] = color[j];
    }


    Update(text);

    LOGI("End of creating text.");
}

void mjGraphicText::SetRenderScale(float renderScale)
{
    this->renderScale = renderScale;
    for (int i = 0; i < usedLength; i++)
    {
        textVector[i]->scale.Set(textVector[i]->charWidth*renderScale, textVector[i]->charHeight*renderScale, 1);
    }
}


void mjGraphicText::SetPositionScale(float positionScale)
{

    this->positionScale = positionScale;
    float displacement = 0;

    for (int i = 0; i < usedLength; i++)
    {
        textVector[i]->pos.y = pos.y + (textVector[i]->bitmapTop - textVector[i]->charHeight)*0.003; //FIXME: is this value fixed forever?
        textVector[i]->pos.x = pos.x + (displacement + textVector[i]->bitmapLeft + textVector[i]->manualRelocation)*positionScale;
        displacement +=  (textVector[i]->advanceX/64.0);
    }
}
void mjGraphicText::SetColor(float* color)
{
    for (int j = 0; j < 4; j++)
    {
        this->color[j] = color[j];
    }

    for (int i = 0; i < usedLength; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            textVector[i]->extraColorForTexture[j] = color[j];
        }
    }
}
void mjGraphicText::Update(const char *text)
{
    this->text;

    int bytePos = 0;

    int currentCharPos = 0;

    int totalByteLength = strnlen(text, 1024);

    while (bytePos < totalByteLength)
    {
        int thisCharLength = ftgl::utf8_surrogate_len(&text[bytePos]);

        if (!thisCharLength)
        {
            LOGI("mjGraphicText: Invalid char in %s [%d]!", text, bytePos);
            break;
        }/* else
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
        }*/
        unsigned long thisCharLong = ftgl::utf8_to_utf32(&(text[bytePos]));
        //LOGI("Char: (%lu) %s", thisCharLong, &(text[pos]));

        mjGraphicCharObject* charObject;

        if (currentCharPos < textVector.size())
        {
            charObject = textVector[currentCharPos];
            mjGraphicCharObjectResource* resource = resourceManager->FetchGraphicChar(fontResource, fontSize, thisCharLong);
            charObject->SetGraphicCharResource(resource);
        } else
        {
            charObject = new mjGraphicCharObject(resourceManager, fontResource, fontSize, thisCharLong, renderScale);
            textVector.push_back(charObject);
        }

        if (charObject->charRatio > 4)
        {

            charObject->manualRelocation = -charObject->charWidth; //FIXME: Why is this necessary??
        }
        //LOGI("width: %d, bitmapLeft: %f, advance: %f", charObject->charWidth, charObject->bitmapLeft, (charObject->advanceX/64.0) );

        currentCharPos++;
        bytePos += thisCharLength;
    }
    usedLength = currentCharPos;

    SetPositionScale(positionScale);
    SetRenderScale(renderScale);
    SetColor(color);

}


}
