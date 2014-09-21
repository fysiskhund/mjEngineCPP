#include "mjImageLoader.h"



namespace mjEngine{

mjImageLoader::mjImageLoader()
{

}


bool mjImageLoader::Load(const char* name)
{
	// This procedure is based in Morten Nobel's
	// http://blog.nobel-joergensen.com/2010/11/07/loading-a-png-as-texture-in-opengl-using-libpng/
	// with many thanks!

	//LOGI("Name is %s start", name);
	png_structp png_ptr;
	    png_infop info_ptr;
	    unsigned int sig_read = 0;
	    int color_type, interlace_type;
	    FILE *fp;

	    if ((fp = fopen(name, "rb")) == NULL)
	        return false;

	    /* Create and initialize the png_struct
	     * with the desired error handler
	     * functions.  If you want to use the
	     * default stderr and longjump method,
	     * you can supply NULL for the last
	     * three parameters.  We also supply the
	     * the compiler header file version, so
	     * that we know if the application
	     * was compiled with a compatible version
	     * of the library.  REQUIRED
	     */
	    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
	                                     NULL, NULL, NULL);
	    //LOGI("Name is %s after create_read_Struct", name);
	    if (png_ptr == NULL) {
	        fclose(fp);
	        return false;
	    }

	    /* Allocate/initialize the memory
	     * for image information.  REQUIRED. */
	    info_ptr = png_create_info_struct(png_ptr);
	    //LOGI("Name is %s after png_create_info_truct", name);
	    if (info_ptr == NULL) {
	        fclose(fp);
	        png_destroy_read_struct(&png_ptr, NULL, NULL);
	        return false;
	    }

	    /* Set error handling if you are
	     * using the setjmp/longjmp method
	     * (this is the normal method of
	     * doing things with libpng).
	     * REQUIRED unless you  set up
	     * your own error handlers in
	     * the png_create_read_struct()
	     * earlier.
	     */
	    if (setjmp(png_jmpbuf(png_ptr))) {
	        /* Free all of the memory associated
	         * with the png_ptr and info_ptr */
	        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	        fclose(fp);
	        /* If we get here, we had a
	         * problem reading the file */
	        return false;
	    }

	    /* Set up the output control if
	     * you are using standard C streams */
	    png_init_io(png_ptr, fp);

	    /* If we have already
	     * read some of the signature */
	    png_set_sig_bytes(png_ptr, sig_read);

	    /*
	     * If you have enough memory to read
	     * in the entire image at once, and
	     * you need to specify only
	     * transforms that can be controlled
	     * with one of the PNG_TRANSFORM_*
	     * bits (this presently excludes
	     * dithering, filling, setting
	     * background, and doing gamma
	     * adjustment), then you can read the
	     * entire image (including pixels)
	     * into the info structure with this
	     * call
	     *
	     * PNG_TRANSFORM_STRIP_16 |
	     * PNG_TRANSFORM_PACKING  forces 8 bit
	     * PNG_TRANSFORM_EXPAND forces to
	     *  expand a palette into RGB
	     */
	    //LOGI("Name is %s before read_png", name);
	    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
	    //LOGI("Name is %s after read_png", name);

	    int bit_depth;
	    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
	                 &interlace_type, NULL, NULL);

	    hasAlpha = (color_type == PNG_COLOR_TYPE_RGBA);


	    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);


	    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);




	    //LOGI("Name is %s before new unsigned whatever", name);
	    imageData = new unsigned char[row_bytes * height];
	    //LOGI("Name is %s after new unsigned whatever", name);

	    for (int i = 0; i < height; i++) {
	        // note that png is ordered top to
	        // bottom, but OpenGL expect it bottom to top
	        // so the order or swapped
	    	//memcpy(imageData+(row_bytes * (height-1-i)), row_pointers[i], row_bytes);

	    	// Apparently the image is not reversed anymore, so I changed it to just copying stuff around
	    	memcpy(imageData+(row_bytes * (i)), row_pointers[i], row_bytes);



	    }

	    /* Clean up after the read,
	     * and free any memory allocated */
	    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	    //LOGI("Name is %s after destroying read structures", name);
	    /* Close the file */
	    fclose(fp);
	    return true;
}

GLuint mjImageLoader::SendToGL(GLfloat textureWrapParam)
{
	GLuint textures[1];
	glGenTextures(1, &textures[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	// Set parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapParam);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapParam);
	//LOGI("Texture hasAlpha: %d", hasAlpha);
	glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha? GL_RGBA : GL_RGB, width, height, 0, hasAlpha? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imageData);//testImage.pixel_data);
	return textures[0];
}
GLuint mjImageLoader::LoadToGLAndFreeMemory(const char* fileName, GLfloat textureWrapParam)
{
	GLuint result = 0;
	//LOGI("At load for %s", fileName);
	if (Load(fileName))
	{
		result = SendToGL(textureWrapParam);
		//LOGI("Loaded %s to texture %d",  fileName, result);

		//delete [] imageData;
	}
	return result;
}
GLuint mjImageLoader::LoadToGLAndFreeMemory(const char* fileName)
{
	return LoadToGLAndFreeMemory(fileName, GL_REPEAT);
}

}// namespace mjEngine



