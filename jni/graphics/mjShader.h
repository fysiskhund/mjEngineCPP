/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJSHADER_H
#define MJSHADER_H

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "mjModelMesh.h"

#define  LOG_TAG    "mj"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

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
			float* modelMatrix, float* modelViewProjectionMatrix){}; // Gets called before drawing something
	GLuint LoadShader(GLenum shaderType, const char* pSource);
	void CreateProgram(const char* vertexShadercode, const char* fragmentShaderCode);
};

}

#endif
