#ifndef MJMULTIPLATFORM_H
#define MJMULTIPLATFORM_H

// Macros for choosing GL versions
#ifdef USE_GLES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#ifdef WIN32
    #include <Windows.h>
    unsigned strnlen(const char* str, unsigned n);
    #define png_uint_32 unsigned
    #define png_byte char
#endif // WIN32
    #define GLEW_STATIC
    #include <GL/glew.h>
    #include <GL/gl.h>
    #include <SDL2/SDL.h>
#endif // !USE_GLES

/*class glMultiPlatform
{
public:
    static void CreateGLContext();
};*/
// Decided not to store the pathPrefix in N places. The mjResourceManager should be enough

#endif // MJMULTIPLATFORM_H
