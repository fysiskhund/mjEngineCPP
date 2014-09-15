/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJSHADER_H
#define MJSHADER_H



#include "mjModelMesh.h"
#include "../mjVector3.h"

#ifdef ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

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
			float* modelMatrix, float* modelViewProjectionMatrix)= 0; // Gets called before drawing something
	GLuint LoadShader(GLenum shaderType, const char* pSource);
	void CreateProgram(const char* vertexShadercode, const char* fragmentShaderCode);
};

}

#endif
