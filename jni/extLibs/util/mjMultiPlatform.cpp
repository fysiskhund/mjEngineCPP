#include "mjMultiPlatform.h"

#ifdef WIN32
unsigned strnlen(const char* str, unsigned n)
{
	return strlen(str);
}

#endif

void mjMultiPlatform::AddCommandForJNI(std::string& command)
{
	if (!mjMultiPlatform::commandsForJNIPresent)
	{
		mjMultiPlatform::commandsForJNI = command;
		mjMultiPlatform::commandsForJNIPresent = true;
	} else
	{
		mjMultiPlatform::commandsForJNI += "\n" + command;
	}
}
std::string mjMultiPlatform::commandsForJNI = "";
bool mjMultiPlatform::commandsForJNIPresent = false;


void checkGlError(const char *op)
{
                for (GLint error = glGetError(); error; error
                     = glGetError()) {
                    printf("after %s() glError (0x%x)\n", op, error);
                }
            }
/*void glMultiPlatform::CreateGLContext()
{

}*/
