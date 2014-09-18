/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJIMAGELOADER_H
#define MJIMAGELOADER_H

#include <stdlib.h>
#include <stdarg.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "../extLibs/png/include/png.h"
#include "../extLibs/logger/mjLog.h"
namespace mjEngine{

class mjImageLoader
{
public:





	png_uint_32 width, height;


	mjImageLoader();

	GLuint LoadToGLAndFreeMemory(const char *name);

private:
	png_uint_32 rowbytes;
	int x, y;
	bool hasAlpha;
	GLubyte *imageData;

	png_byte color_type;
	png_byte bit_depth;

	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep * row_pointers;

	bool Load(const char *name);

	GLuint SendToGL();

};

}// namespace mjEngine
#endif
