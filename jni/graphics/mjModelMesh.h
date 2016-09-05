/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJMODELMESH_H
#define MJMODELMESH_H

#include <stdio.h>
#include <extLibs/util/mjMultiPlatform.h>
#include <extLibs/logger/mjLog.h>

namespace mjEngine{
class mjModelMesh
{
public:
	char* name = NULL;
	char* material = NULL;
	char* shaderName = NULL;
	int meshNumber;
    int mjShaderListIndex = -1;
	unsigned short* drawOrderBuffer;
	unsigned int drawOrderCount;

    float* vertexBuffer =  NULL;
    float* normalBuffer =  NULL;
    float* textureCoordsBuffer =  NULL;

    
    GLuint elementBufferID;
    int glTexture = -1;





	mjModelMesh();


};
}// namespace mjEngine
#endif
