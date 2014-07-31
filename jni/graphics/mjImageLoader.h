#ifndef MJIMAGELOADER_H
#define MJIMAGELOADER_H

#include <stdlib.h>
#include <stdarg.h>

#include "../extLibs/png/include/png.h"
namespace mjEngine{

class mjImageLoader
{
public:
	mjImageLoader(char* file_name);

	int x, y;

	int width, height, rowbytes;
	png_byte color_type;
	png_byte bit_depth;

	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep * row_pointers;
	void abort_(const char * s, ...);
};

}// namespace mjEngine
#endif
