#ifndef MJMULTIPLATFORM_H
#define MJMULTIPLATFORM_H

// Macros for choosing GL versions
#ifdef USE_GLES2
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>

    #define MJ_LEFT_JOYSTICK_X 0
    #define MJ_LEFT_JOYSTICK_Y 1
    #define MJ_RIGHT_JOYSTICK_X 3
    #define MJ_RIGHT_JOYSTICK_Y 4

#else

    #define MJ_LEFT_JOYSTICK_X 0
    #define MJ_LEFT_JOYSTICK_Y 1
    #define MJ_RIGHT_JOYSTICK_X 2
    #define MJ_RIGHT_JOYSTICK_Y 3

    #ifdef OSX
        #include <OpenGL/gl.h>
        #include <OpenGL/glu.h>
        #include <OpenGL/glext.h>
    #else

        #ifdef WIN32

            #include <Windows.h>
            unsigned strnlen(const char* str, unsigned n);
            #define png_uint_32 unsigned
            #define png_byte char

        #endif //! WIN32



        #define GLEW_STATIC
        #include <GL/glew.h>
        #include <GL/gl.h>
        #include <SDL2/SDL.h>

    #endif // !OSX

#endif // !USE_GLES

#include <string>

class mjMultiPlatform
{
public:
    static void AddCommandForJNI(std::string& command);
    static std::string commandsForJNI;
    static bool commandsForJNIPresent;
};


#endif // MJMULTIPLATFORM_H
