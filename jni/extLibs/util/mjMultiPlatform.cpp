#include "mjMultiPlatform.h"

#ifdef WIN32
unsigned strnlen(const char* str, unsigned n)
{
	return strlen(str);
}

#endif

std::string mjMultiPlatform::commandsForJNI = "";
bool mjMultiPlatform::commandsForJNIPresent = false;
/*void glMultiPlatform::CreateGLContext()
{

}*/
