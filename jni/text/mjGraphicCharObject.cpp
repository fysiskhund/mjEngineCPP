#include "mjGraphicCharObject.h"

namespace mjEngine {


// FIXME: Cleanup missing.

mjGraphicCharObject::mjGraphicCharObject(mjResourceManager* resourceManager, mjFontResource* fontResource, int fontSize, char* charToRender)
    : mjObject(resourceManager)
{
    this->fontResource = fontResource;
    this->charToRender = new char[strnlen(charToRender, 8)+1];
    this->fontSize = fontSize;
    strncpy(this->charToRender, charToRender, strnlen(charToRender, 8)+1);


    charToRenderFT = FT_Get_Char_Index(fontResource->face, ftgl::utf8_to_utf32(charToRender));

    model = resourceManager->FetchModel("sprite.mesh.xml");
    customShaders = new std::vector<mjShader*>;
    mjShaderResource* textShaderResource = resourceManager->FetchShader("text");

    customShaders->push_back(textShaderResource->shader);
    customTextures = new int[1];
    GenerateTexture();

}

void mjGraphicCharObject::GenerateTexture()
{
    FT_Set_Pixel_Sizes(fontResource->face, 0, fontSize);
    if (FT_Load_Glyph(fontResource->face, charToRenderFT, FT_LOAD_RENDER))
    {
        LOGI("Error while rendering glyph");
    }



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
