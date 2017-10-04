#ifndef MJMULTIPLATFORM_H
#define MJMULTIPLATFORM_H

// Macros for choosing GL versions
#ifdef USE_GLES2
#ifndef IOS
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
#else
    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>

    #define glGenVertexArrays glGenVertexArraysOES
    #define glBindVertexArray glBindVertexArrayOES
#endif


#else



    #ifdef OSX

// I'M DIFFERENT!!!!!!!!!!!
// DIFFERENT!!!!!!!!!!!!!!1!!!!!!!!!!!!!!!!
// OMVFG!!!!!!

        #include <OpenGL/gl3.h>
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
#endif // DESKTOP_SDL

void checkGlError(const char* op);
void mjGlErrorCallback(GLenum source,
                       GLenum type,
                       GLuint id,
                       GLenum severity,
                       GLsizei length,
                       const GLchar *message,
                       const void *userParam);

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


#ifdef ANDROID_ASSMAN
#include <android/asset_manager.h>
#else
#define AAssetManager int
#endif

#include <string>

class mjMultiPlatform
{
public:
    static void AddCommandForJNI(std::string& command);
    static std::string commandsForJNI;
    static bool commandsForJNIPresent;
    static void RequestFullscreenAdvertisement();
};


#endif // MJMULTIPLATFORM_H
