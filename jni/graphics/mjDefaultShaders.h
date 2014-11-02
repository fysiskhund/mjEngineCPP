/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJDEFAULTSHADERS_H
#define MJDEFAULTSHADERS_H

#include "../extLibs/util/mjMultiPlatform.h"

#include "mjShader.h"
#include "../core/mjVector3.h"
#include <string.h>

#include "../extLibs/logger/mjLog.h"

namespace mjEngine{

class mjDefaultShaders:  public mjShader
{
	public:
	mjDefaultShaders();
	void Run(mjModelMesh* mesh,
			float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
			float* modelMatrix, float* modelViewProjectionMatrix ) override;
	static const char* simpleVertexShaderCode; // The simple shaders can be used in the skybox
	static const char* simpleFragmentShaderCode;
	static const char* vanillaVertexShaderCode; // Vanilla shaders give a flat shading of surfaces
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
	GLuint maMMatrixHandle;
	GLuint uDiffuseLightDirectionHandle;
	GLuint uDiffuseLightColorHandle;
	GLuint uAmbientLightColorHandle;
	//GLuint maMVMatrixHandle;
	private:
		float diffuseLightDirectionArray[3];
};
}
#endif
