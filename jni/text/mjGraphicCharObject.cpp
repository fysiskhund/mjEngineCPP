#include "mjGraphicCharObject.h"

namespace mjEngine {


// FIXME: Cleanup missing.

mjGraphicCharObject::mjGraphicCharObject(mjResourceManager* resourceManager, mjFontResource* fontResource, int fontSize,
                                         unsigned long charToRenderLong, float renderScale, float positionScale)
    : mjObject(resourceManager)
{
    this->fontResource = fontResource;
    this->fontSize = fontSize;


    this->charToRenderLong = charToRenderLong;

    model = resourceManager->FetchModel("sprite.mesh.xml");
    customShaders = new std::vector<mjShader*>;
    mjShaderResource* textShaderResource = resourceManager->FetchShader("text");

    customShaders->push_back(textShaderResource->shader);
    customTextures = new int[1];
    GenerateTexture();
    scale.MulScalar(renderScale);

}

void mjGraphicCharObject::GenerateTexture()
{
    FT_Set_Pixel_Sizes(fontResource->face, 0, fontSize);
    if (FT_Load_Char(fontResource->face, charToRenderLong, FT_LOAD_RENDER))
    {
        LOGI("Error while rendering glyph");
    }

    charRatio = ((float)fontResource->face->glyph->bitmap.rows) / ((float)fontResource->face->glyph->bitmap.width);
    charOffsetX = fontResource->face->glyph->bitmap_left;
    charOffsetY = fontResource->face->glyph->bitmap_top;
    nextCharOffsetX = (fontResource->face->glyph->advance.x) >> 6; // Bitshift by 6 to get value in pixels (2^6 = 64)

    scale.Set(1, charRatio, 1);
    //modelOffset.Set(charOffsetX, charOffsetY, 0);



    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, (GLuint*) customTextures);

    glBindTexture(GL_TEXTURE_2D, customTextures[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    // Next ifdef: GL3 doesn't have GL_LUMINANCE but has GL_RED. GL ES 2 doesn't have GL_RED but has GL_LUMINANCE.
    // Slow clap.

#ifdef USE_GL3
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        fontResource->face->glyph->bitmap.width,
        fontResource->face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );
#else
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_LUMINANCE,
        fontResource->face->glyph->bitmap.width,
        fontResource->face->glyph->bitmap.rows,
        0,
        GL_LUMINANCE,
        GL_UNSIGNED_BYTE,
        fontResource->face->glyph->bitmap.buffer
    );
#endif

}

}
