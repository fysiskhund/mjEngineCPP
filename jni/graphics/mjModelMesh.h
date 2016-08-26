/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJMODELMESH_H
#define MJMODELMESH_H

#include <stdio.h>
#include <extLibs/util/mjMultiPlatform.h>

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

    float* vertexBuffer =  NULL;
    float* normalBuffer =  NULL;
    float* textureCoordsBuffer =  NULL;

	int glTexture;
    
    GLuint elementBufferID;

	mjModelMesh();


};
}// namespace mjEngine
#endif
