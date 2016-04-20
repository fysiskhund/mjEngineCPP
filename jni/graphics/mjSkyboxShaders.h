#ifndef MJ_SKYBOX_SHADERS
#define MJ_SKYBOX_SHADERS


#include <string.h>
#include "../extLibs/util/mjMultiPlatform.h"


#include "mjShader.h"
#include "../core/mjVector3.h"

namespace mjEngine {

class mjSkyboxShaders: public mjShader{
public:
	mjSkyboxShaders();

	void Run(mjModelMesh* mesh,
			float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
            float* modelMatrix, float* modelViewProjectionMatrix, int glTexture ) override;

#ifdef USE_ASSIMP
    void RunForAssimp(const aiMesh* assimpMesh, mjModelMesh* mjMesh,
                      float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
                      float* modelMatrix, float* modelViewProjectionMatrix, int glTexture) override  ;
#endif

	static const char* skyboxVertexShaderCode; // Vanilla shaders give a flat shading of surfaces
	static const char* skyboxFragmentShaderCode;



	mjVector3 diffuseLightDirection;
	float diffuseLightColor[4];
	float ambientLightColor[4];

	// Handles
	GLuint maPositionHandle;
	GLuint maTextureCoordHandle;
	GLuint maTextureHandle;
	GLuint maMVPMatrixHandle;
	GLuint boxTextures[6];
	//GLuint maMVMatrixHandle;

};

}




#endif
