/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJMODELMESH_H
#define MJMODELMESH_H


namespace mjEngine{
class mjModelMesh
{
public:
	char* name;
	char* material;
	char* shaderName;
	int mjShaderListIndex;
	unsigned short* drawOrderBuffer;
	unsigned int drawOrderCount;

	int glTexture;

	mjModelMesh();


};
}// namespace mjEngine
#endif
