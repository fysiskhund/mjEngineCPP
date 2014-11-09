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
#endif // DESKTOP_SDL
#ifdef USE_LIBPNG
#include "../extLibs/png/include/png.h"
#endif
#include "../extLibs/logger/mjLog.h"


namespace mjEngine{

class mjImageLoader
{
public:





	unsigned width, height;


	mjImageLoader();

	GLuint LoadToGLAndFreeMemory(const char *name);
	GLuint LoadToGLAndFreeMemory(const char* fileName, GLfloat textureWrapParam);

private:
	unsigned rowbytes;
	int x, y;
	bool hasAlpha;
	GLubyte *imageData;

	char color_type;
	char bit_depth;

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
