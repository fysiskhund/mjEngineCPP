#ifndef MJMULTIPLATFORM_H
#define MJMULTIPLATFORM_H

// Macros for choosing GL versions
#ifdef USE_GLES2
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>



#else



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


    #endif // !OSX

#endif // !USE_GLES

#ifdef DESKTOP_SDL
    #include <SDL2/SDL.h>

            void checkGlError(const char* op);


#endif // USE_SDL_AUDIO

// Set up joystick
#ifdef WIN32
    #define MJ_LEFT_JOYSTICK_X 0
    #define MJ_LEFT_JOYSTICK_Y 1
    #define MJ_RIGHT_JOYSTICK_X 2
    #define MJ_RIGHT_JOYSTICK_Y 3
#else
    #ifdef GNULINUX
        #define MJ_LEFT_JOYSTICK_X 0
        #define MJ_LEFT_JOYSTICK_Y 1
        #define MJ_RIGHT_JOYSTICK_X 3
        #define MJ_RIGHT_JOYSTICK_Y 4
    #else
        #define MJ_LEFT_JOYSTICK_X 0
        #define MJ_LEFT_JOYSTICK_Y 1
        #define MJ_RIGHT_JOYSTICK_X 3
        #define MJ_RIGHT_JOYSTICK_Y 4
    #endif // GNULINUX
#endif // WIN32



#include <string>

class mjMultiPlatform
{
public:
    static void AddCommandForJNI(std::string& command);
    static std::string commandsForJNI;
    static bool commandsForJNIPresent;
};


#endif // MJMULTIPLATFORM_H
