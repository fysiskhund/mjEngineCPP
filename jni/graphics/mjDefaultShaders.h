/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJDEFAULTSHADERS_H
#define MJDEFAULTSHADERS_H

#include <extLibs/util/mjMultiPlatform.h>

#include <graphics/mjShader.h>
#include <core/mjVector3.h>
#include <string.h>

#include <extLibs/logger/mjLog.h>

namespace mjEngine{

class mjDefaultShaders:  public mjShader
{
	public:
	mjDefaultShaders();
	void Run(mjModelMesh* mesh,
			float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
            float* modelMatrix, float* modelViewProjectionMatrix, int glTexture) override;

#ifdef USE_ASSIMP
    void RunForAssimp(const aiMesh* assimpMesh, mjModelMesh* mjMesh,
                      float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
                      float* modelMatrix, float* modelViewProjectionMatrix, int glTexture)  override;
#endif

	static const char* simpleVertexShaderCode; // The simple shaders can be used in the skybox
	static const char* simpleFragmentShaderCode;
	static const char* vanillaVertexShaderCode; // Vanilla shaders give a flat shading of surfaces
	static const char* vanillaFragmentShaderCode;
	static const char* vanillaFragmentShaderCode_GL3_3;



	mjVector3 diffuseLightDirection;
	float diffuseLightColor[4];
	float ambientLightColor[4];

	// Handles
    GLint maPositionHandle;
    GLint maNormalHandle;
    GLint maTextureCoordHandle;
    GLint maTextureHandle;
    GLint maMVPMatrixHandle;
    GLint maMMatrixHandle;
    GLint uDiffuseLightDirectionHandle;
    GLint uDiffuseLightColorHandle;
    GLint uAmbientLightColorHandle;
    //GLint maMVMatrixHandle;
	private:
		float diffuseLightDirectionArray[3];

};
}
#endif
