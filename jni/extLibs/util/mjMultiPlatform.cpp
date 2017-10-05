#include "mjMultiPlatform.h"

#ifdef WIN32
unsigned strnlen(const char* str, unsigned n)
{
	return strlen(str);
}

#endif

void mjMultiPlatform::AddCommandForJava(std::string& command)
{
    if (!mjMultiPlatform::commandsForJavaPresent)
	{
        mjMultiPlatform::commandsForJava = command;
        mjMultiPlatform::commandsForJavaPresent = true;
	} else
	{
        mjMultiPlatform::commandsForJava += "\n" + command;
    }
}

void mjMultiPlatform::RequestFullscreenAdvertisement()
{
    std::string fullScreenAdvScreen = "55:fullscreenRequested";
    mjMultiPlatform::AddCommandForJava(fullScreenAdvScreen);
}

void mjMultiPlatform::FlushCommandsForJava()
{
    commandsForJava = "";
    commandsForJavaPresent = false;
}
std::string mjMultiPlatform::commandsForJava = "";
bool mjMultiPlatform::commandsForJavaPresent = false;


void checkGlError(const char *op)
{
    for (GLint error = glGetError(); error; error
         = glGetError()) {
        printf("after %s() glError (0x%x)\n", op, error);
        printf(" ");

    }
}

void mjGlErrorCallback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar *message,
            const void *userParam)
{
    printf("Debug callback:\n"
           "type: %d\n"
           "id: %d\n"
           "severity: %d\n"
           "length: %d\n"
           "message: %s\n", type, id, severity, length, message);
    if (severity != 33387)
    {
        printf("\n");
    }
}

/*void glMultiPlatform::CreateGLContext()
{

}*/
