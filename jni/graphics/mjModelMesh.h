/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJMODELMESH_H
#define MJMODELMESH_H

#include <stdio.h>

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

	mjModelMesh();


};
}// namespace mjEngine
#endif
