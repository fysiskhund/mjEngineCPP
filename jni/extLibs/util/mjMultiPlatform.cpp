#include "mjMultiPlatform.h"

#ifdef WIN32
unsigned strnlen(const char* str, unsigned n)
{
	return strlen(str);
}

#endif
/*void glMultiPlatform::CreateGLContext()
{

}*/
