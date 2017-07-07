#include "mjGraphicCharObject.h"

namespace mjEngine {


mjGraphicCharObject::mjGraphicCharObject(mjResourceManager* resourceManager, mjFontResource* fontResource, int fontSize,
                                         unsigned long charToRenderLong, float renderScale)
    : mjObject(resourceManager)
{
#ifndef NODEBUGDELETEMSG
    LOGI("mjGraphicChar() %x", this);
#endif
    this->fontResource = fontResource;
    this->fontSize = fontSize;
    this->renderScale = renderScale;


    this->charToRenderLong = charToRenderLong;


    model = resourceManager->FetchModel("models/sprite.mesh.xml");
    customShaders = new std::vector<mjShader*>;
    mjShaderResource* textShaderResource = resourceManager->FetchShader("text");

    customShaders->push_back(textShaderResource->shader);
    customTextures = new int[1];

    SetGraphicCharResource(resourceManager->FetchGraphicChar(fontResource, fontSize, charToRenderLong));
}

void mjGraphicCharObject::SetGraphicCharResource(mjGraphicCharObjectResource* resource)
{
    this->graphicCharObjectResource = resource;

    this->charToRenderLong = resource->charToRenderLong;
    this->bitmapLeft = resource->bitmapLeft;
    this->bitmapTop = resource->bitmapTop;
    this->charWidth = resource->charWidth;
    this->charHeight = resource->charHeight;
    this->charRatio = resource->charRatio;
    this->advanceX = resource->advanceX;


    this->fontResource = resource->fontResource;
    this->fontSize = resource->fontSize;
    this->customTextures[0] = resource->texture;



}
mjGraphicCharObject::~mjGraphicCharObject()
{
#ifndef NODEBUGDELETEMSG
    LOGI("~mjGraphicChar %x", this);
#endif
    //LOGI("deadsies x_X %x", this);
    delete customShaders;
    delete [] customTextures;
}



}
