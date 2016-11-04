#include "mjGraphicCharObjectResource.h"



namespace mjEngine {


mjGraphicCharObjectResource::mjGraphicCharObjectResource(mjFontResource* fontResource, int fontSize, unsigned long charToRenderLong)
{
    this->fontResource = fontResource;
    this->fontSize = fontSize;


    this->charToRenderLong = charToRenderLong;
    GenerateTexture();
}

void mjGraphicCharObjectResource::GenerateTexture()
{

    FT_Set_Pixel_Sizes(fontResource->face, 0, fontSize);
    if (FT_Load_Char(fontResource->face, charToRenderLong, FT_LOAD_RENDER))
    {
        LOGI("Error while rendering glyph");
    }

    FT_GlyphSlot charGlyph = fontResource->face->glyph;

    charWidth = charGlyph->bitmap.width;
    charHeight = charGlyph->bitmap.rows;

    charRatio = ((float)charGlyph->bitmap.rows) / ((float)charGlyph->bitmap.width);
    bitmapLeft = charGlyph->bitmap_left;
    bitmapTop = charGlyph->bitmap_top;
    advanceX = charGlyph->advance.x;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

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
        charWidth,
        charHeight,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        charGlyph->bitmap.buffer
    );
#else
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_LUMINANCE,
        charWidth,
        charHeight,
        0,
        GL_LUMINANCE,
        GL_UNSIGNED_BYTE,
        charGlyph->bitmap.buffer
    );
#endif
}


}
