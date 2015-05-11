/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJMODELMESH_H
#define MJMODELMESH_H

#include <stdio.h>
//#include "../extLibs/util/mjMultiPlatform.h"

namespace mjEngine{
class mjModelMesh
{
public:
	char* name = NULL;
	char* material = NULL;
	char* shaderName = NULL;
	int meshNumber;
	int mjShaderListIndex;
	unsigned short* drawOrderBuffer;
	unsigned int drawOrderCount;

	int glTexture;
    
    /*#ifdef OSX
        // Buffers needed for CORE profile compliance
        GLuint vertexArrayObject;
        GLuint objectBuffers[3]; // Position, normal and texcoord buffers
    #endif*/

	mjModelMesh();


};
}// namespace mjEngine
#endif
