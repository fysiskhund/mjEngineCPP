#include "mjGraphicText.h"

namespace mjEngine {


mjGraphicText::mjGraphicText(mjResourceManager* resourceManager, const char* text, const char* font, int fontSize,
                             float renderScale, float positionScaleHz, float positionScaleVr, float* color, mjVector3& position,
                             TextAlignment alignment)
    : mjUIObject(resourceManager)
{

#ifndef NODEBUGDELETEMSG
    LOGI("mjGraphicText() %x", this);
#endif

    dir.Set(0,0,1);
    scale.Set(1,1,1);
    up.Set(0,1,0);
    this->alignment = alignment;
    this->text = text;
    this->resourceManager = resourceManager;
    this->fontSize = fontSize;
    this->renderScale = renderScale;
    this->positionScaleHz = positionScaleHz;
    this->positionScaleVr = positionScaleVr;
    this->pos.CopyFrom(position);
    // Determine how many chars we're going to render




    std::string fontPath = font;

    fontResource = resourceManager->FetchFont(fontPath);

    for (int j = 0; j < 4; j++)
    {
        this->color[j] = color[j];
    }


    // Normally these objects are created while there is a GL context available, so
    // its text gets updated immediately on creation.
    UpdateTextStatic(text);
    UpdateModelMatrix();

    LOGI("End of creating text.");
}

void mjGraphicText::SetRenderScale(float renderScale)
{
    this->renderScale = renderScale;
    for (int i = 0; i < usedLength; i++)
    {
        ((mjGraphicCharObject*) subObjects[i])->scale.Set(((mjGraphicCharObject*) subObjects[i])->charWidth*renderScale, ((mjGraphicCharObject*) subObjects[i])->charHeight*renderScale, 1);
    }
}


void mjGraphicText::SetPositionScale(float positionScaleHz)
{

    this->positionScaleHz = positionScaleHz;
    float displacement = 0;

    for (int i = 0; i < usedLength; i++)
    {
        mjGraphicCharObject* subCharObj = (mjGraphicCharObject* ) subObjects[i];

        subCharObj->pos.y = (subCharObj->bitmapTop - subCharObj->charHeight)*positionScaleVr; //FIXME: is this value fixed forever?
        subCharObj->pos.x = (displacement + subCharObj->bitmapLeft)*positionScaleHz;
        displacement +=  subCharObj->advanceX >> 6;
    }
    totalWidth = displacement;

    switch(alignment)
    {
    case ALIGNMENT_LEFT:
        // nothing
        break;
    case ALIGNMENT_CENTER:
        displacement *= 0.5;
    case ALIGNMENT_RIGHT:
        //LOGI("posX -= %f ", displacement);
        for (int i =0; i < usedLength; i++)
        {

            ((mjGraphicCharObject*) subObjects[i])->pos.x -= displacement*positionScaleHz;
        }
        break;
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
            ((mjGraphicCharObject*) subObjects[i])->extraColorForTexture[j] = color[j];
        }
    }
}

void mjGraphicText::UpdateModelMatrix()
{
    Matrix4::GetPositionScaleAndRotationMatrix(pos, dir, up, scale, modelMatrix);
}

void mjGraphicText::UpdateText(const char* format, ...)
{
    char buffer[1024];

    va_list argptr;
    va_start(argptr, format);
    vsnprintf(buffer, 1024, format, argptr);
    va_end(argptr);

    this->text =  buffer;

    if (immediateUpdate)
    {
         UpdateTextStatic(buffer);
    } else
    {
        requiresTextUpdate = true;
    }

}

void mjGraphicText::UpdateTextStatic(const char* text)
{

    int totalByteLength = strnlen(text, 1024);


    this->text = text;

    int bytePos = 0;

    int currentCharPos = 0;



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
                    charCharCharmander[j] = text[bytePos + j];
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
        //LOGI("CharLong: (%lu)", thisCharLong);

        mjGraphicCharObject* charObject;

        if (currentCharPos < subObjects.size())
        {
            charObject = (mjGraphicCharObject*) subObjects[currentCharPos];
            mjGraphicCharObjectResource* resource = resourceManager->FetchGraphicChar(fontResource, fontSize, thisCharLong);
            charObject->SetGraphicCharResource(resource);
        } else
        {
            charObject = new mjGraphicCharObject(resourceManager, fontResource, fontSize, thisCharLong, renderScale);
            subObjects.push_back(charObject);
        }

        /*if (charObject->charRatio > 4)
        {

            charObject->manualRelocation = -charObject->charWidth; //FIXME: Why is this necessary??
        }*/
        //LOGI("width: %d, bitmapLeft: %f, advance: %f", charObject->charWidth, charObject->bitmapLeft, (charObject->advanceX/64.0) );

        currentCharPos++;
        bytePos += thisCharLength;
    }
    usedLength = currentCharPos;


    SetDrawToSubObject(currentCharPos-1);
    //drawToSubObject = currentCharPos;

    SetPositionScale(positionScaleHz);
    SetRenderScale(renderScale);
    SetColor(color);

    //LOGI("drawToSubObject: %d", drawToSubObject);
}

void mjGraphicText::SetDetailsFromXML(XMLElement* entity)
{
    mjUIObject::SetDetailsFromXML(entity);

    const char* value = entity->Attribute("variable");
    if (value)
    {
        variable = value;
    }

    value = entity->Attribute("content");
    if (value)
    {
        // Forcibly, Update() is needed to properly do this. Unfortunately.
        // This is the only way we can guarantee there will be no crash as everything needs to be generated
        // with a thread that has the GL context available. In other words, the thread running Update(t_elapsed);
        immediateUpdate = false;
        UpdateText(value);
    }

    value = entity->Attribute("textAlignment");
    if (value)
    {
        if (strncmp("center", value, 12) == 0)
        {
            this->alignment = ALIGNMENT_CENTER;
        } else if (strncmp("left", value, 12) == 0)
        {
            this->alignment = ALIGNMENT_LEFT;
        } else if (strncmp("right", value, 12) == 0)
        {
            this->alignment = ALIGNMENT_RIGHT;
        } else
        {
            LOGI("Invalid text alignment: %s", value);
        }
    }
}

void mjGraphicText::ReceiveInternalMessage(void* contents, unsigned int type, void* sender)
{
    if (type == MJ_SET_VARIABLE && !variable.empty())
    {
        std::string strContents = (char*) contents;

        std::string comparison = variable + "=";
        std::size_t comparisonLength = comparison.length();

        std::string variableToSet = strContents.substr(0, comparisonLength);

        // Compare the "variableName=" part of "variableName=value". If it matches then set the new value.
        if (variableToSet.compare(comparison) == 0 )
        {
            // This needs to be very strictly NON-immediate
            UpdateText(strContents.substr(comparison.length()).c_str());

        }
    }
}

void mjGraphicText::Update(double t_elapsed)
{

    mjObject::Update(t_elapsed);

    /* This is so the GL calls can be made when there is a context present
     * otherwise funky things happen, at least in Android..
    */
    if (requiresTextUpdate)
    {
        requiresTextUpdate = false;
        UpdateTextStatic(this->text.c_str());
    }
}



mjGraphicText::~mjGraphicText()
{
#ifndef NODEBUGDELETEMSG
    LOGI("~mjGraphicText %x", this);
#endif
    for (int i = 0; i < subObjects.size(); i++)
    {

        delete subObjects[i];
    }
    subObjects.clear();
}


}
