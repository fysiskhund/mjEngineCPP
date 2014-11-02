/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJIMAGELOADER_H
#define MJIMAGELOADER_H

#include <stdlib.h>
#include <stdarg.h>
#include "../extLibs/util/mjMultiPlatform.h"

#ifdef DESKTOP_SDL
#include <SDL2/SDL_image.h>
#ifndef WIN32
#include "../extLibs/png/include/png.h"
#endif // WIN32
#endif // DESKTOP_SDL
#include "../extLibs/logger/mjLog.h"


namespace mjEngine{

class mjImageLoader
{
public:





	png_uint_32 width, height;


	mjImageLoader();

	GLuint LoadToGLAndFreeMemory(const char *name);
	GLuint LoadToGLAndFreeMemory(const char* fileName, GLfloat textureWrapParam);

private:
	png_uint_32 rowbytes;
	int x, y;
	bool hasAlpha;
	GLubyte *imageData;

	png_byte color_type;
	png_byte bit_depth;

#ifndef DESKTOP_SDL
	png_structp png_ptr;
	png_infop info_ptr;

	png_bytep * row_pointers;
#endif
    int number_of_passes;
#ifdef DESKTOP_SDL
	SDL_Surface* imageSurface;
#endif

	bool Load(const char *name);

	GLuint SendToGL(GLfloat textureWrapParam);



};

}// namespace mjEngine
#endif
