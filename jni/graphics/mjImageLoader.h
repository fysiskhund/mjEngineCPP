/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJIMAGELOADER_H
#define MJIMAGELOADER_H

#include <stdlib.h>
#include <stdarg.h>
#include "extLibs/util/mjMultiPlatform.h"
#include "../util/mjTextureResource.h"

#ifdef DESKTOP_SDL
    #ifdef OSX
        #include <SDL2_image/SDL_image.h>
    #else
        #include <SDL2/SDL_image.h>
    #endif
#endif // DESKTOP_SDL

#ifdef IOS


#elif USE_LIBPNG
#include "../util/mjFileFromArchive.h"
#include "extLibs/png/include/png.h"
#endif


#include "extLibs/logger/mjLog.h"


namespace mjEngine{

class mjImageLoader
{
public:

    



	unsigned width, height;

    // I don't want to include mjResourceManager here, so I hope that by setting this
    // function pointer it will be sufficient
    mjImageLoader(size_t (*ReadFromArchiveFunction)(mjFileFromArchive* mjFile, const unsigned char* buffer, size_t howMany));






    GLuint LoadToGLAndFreeMemory(mjTextureResource* imgRes, GLfloat textureWrapParam);
private:
	unsigned rowbytes;
	int x, y;
	bool hasAlpha;
	GLubyte *imageData;

	char color_type;
	char bit_depth;

    // Function used to give data to libpng when files are read from an archive
    static size_t (*ReadFromArchiveFunction)(mjFileFromArchive* mjFile, const unsigned char* buffer, size_t howMany);


#ifndef DESKTOP_SDL
#ifdef IOS



#elif USE_LIBPNG
	png_structp png_ptr;
	png_infop info_ptr;

	png_bytep * row_pointers;


    // function to replace the standard IO in libpng so we can read from archives
    static void user_read_data(png_structp png_ptr,
            png_bytep data, png_size_t length);

#endif
#endif


    int number_of_passes;
#ifdef DESKTOP_SDL
	SDL_Surface* imageSurface;
    SDL_RWops* memRWop;
#endif

    bool Load(mjTextureResource* imgRes);

	GLuint SendToGL(GLfloat textureWrapParam);



};

}// namespace mjEngine
#endif
