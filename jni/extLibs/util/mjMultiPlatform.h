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
    #define GLEW_STATIC
    #include <GL/glew.h>
#endif // WIN32
    #include <GL/gl.h>
#endif // !USE_GLES

#include <string>

class mjMultiPlatform
{
public:
    std::string prefix;
protected:

private:

};

#endif // MJMULTIPLATFORM_H
