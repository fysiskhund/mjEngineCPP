#ifndef MJIMAGELOADER_H
#define MJIMAGELOADER_H

#include <stdlib.h>
#include <stdarg.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "../extLibs/png/include/png.h"
namespace mjEngine{

class mjImageLoader
{
public:



	int x, y;

	png_uint_32 width, height, rowbytes;
	bool hasAlpha;
	GLubyte *imageData;

	png_byte color_type;
	png_byte bit_depth;

	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep * row_pointers;

	mjImageLoader();

	bool Load(char *name);

};

}// namespace mjEngine
#endif
