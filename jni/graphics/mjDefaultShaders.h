/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJDEFAULTSHADERS_H
#define MJDEFAULTSHADERS_H

#include "mjShader.h"
#include "mjVector3.h"
#include <string.h>

#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "mj"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

namespace mjEngine{

class mjDefaultShaders:  public mjShader
{
	public:
	mjDefaultShaders();
	void Run(mjModelMesh* mesh,
			float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
			float* modelViewProjectionMatrix) override;
	static const char* simpleVertexShaderCode;
	static const char* simpleFragmentShaderCode;
	static const char* vanillaVertexShaderCode;
	static const char* vanillaFragmentShaderCode;


	mjVector3 diffuseLightDirection;
	float diffuseLightColor[4];
	float ambientLightColor[4];

	// Handles
	GLuint maPositionHandle;
	GLuint maNormalHandle;
	GLuint maTextureCoordHandle;
	GLuint maTextureHandle;
	GLuint maMVPMatrixHandle;
	GLuint uDiffuseLightDirectionHandle;
	GLuint uDiffuseLightColorHandle;
	GLuint uAmbientLightColorHandle;
	//GLuint maMVMatrixHandle;
	private:
		float diffuseLightDirectionArray[3];
};
}
#endif
