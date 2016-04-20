/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJSHADER_H
#define MJSHADER_H

#include <stdlib.h>


#ifdef USE_ASSIMP
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif

#include "mjModelMesh.h"
#include "../core/mjVector3.h"

#include "../extLibs/util/mjMultiPlatform.h"

#include "../extLibs/logger/mjLog.h"


namespace mjEngine
{

class mjShader{
public:
	GLuint glProgramHandle;
	GLuint glVertexShaderHandle;
	GLuint glFragmentShaderHandle;
	char* name;

	virtual void Run(mjModelMesh* modelMesh,
			float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
            float* modelMatrix, float* modelViewProjectionMatrix, int glTexture)= 0; // Gets called in order to draw something

#ifdef USE_ASSIMP

    virtual void RunForAssimp(const aiMesh* assimpMesh, mjModelMesh* mjMesh,
                      float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
                      float* modelMatrix, float* modelViewProjectionMatrix, int glTexture) = 0;

#endif


	GLuint LoadShader(GLenum shaderType, const char* pSource);
	void CreateProgram(const char* vertexShadercode, const char* fragmentShaderCode);
};

}

#endif
