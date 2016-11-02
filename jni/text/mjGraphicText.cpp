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
    float displacement = 0;

    while (pos < totalLength)
    {
        int thisCharLength = ftgl::utf8_surrogate_len(&text[pos]);

        if (!thisCharLength)
        {
            LOGI("mjGraphicText: Invalid char in %s [%d]!", text, pos);
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

            LOGI("Char: %s", charCharCharmander);
        }*/
        unsigned long thisCharLong = ftgl::utf8_to_utf32(&(text[pos]));
        LOGI("Char: (%lu) %s", thisCharLong, &(text[pos]));
        mjGraphicCharObject* charObject = new mjGraphicCharObject(resourceManager, fontResource, fontSize, thisCharLong, renderScale, positionScale);

        charObject->pos.x += displacement;

        displacement += charObject->nextCharOffsetX*positionScale;

        textVector.push_back(charObject);
        pos += thisCharLength;
    }
    LOGI("End of creating text.");
}

}
