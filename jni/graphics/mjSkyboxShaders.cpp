#include "mjSkyboxShaders.h"

namespace mjEngine{

mjSkyboxShaders::mjSkyboxShaders()
{
	// Set up shader
	CreateProgram(skyboxVertexShaderCode, skyboxFragmentShaderCode);
	name = new char[7];
	strncpy(name, "skybox", strnlen("skybox", 10)+1);

	maPositionHandle = glGetAttribLocation(glProgramHandle, "vPosition");



	maTextureCoordHandle = glGetAttribLocation(glProgramHandle, "aTexCoordinates");

	// Get the texture handle location
	maTextureHandle = glGetUniformLocation(glProgramHandle, "uTexture");

	maMVPMatrixHandle = glGetUniformLocation(glProgramHandle, "maMVPMatrix");
}


void mjSkyboxShaders::Run(mjModelMesh* mesh,
			float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
            float* modelMatrix, float* modelViewProjectionMatrix, int glTexture)
{

	glUseProgram(glProgramHandle);
	glEnableVertexAttribArray(maPositionHandle);
	glVertexAttribPointer(maPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, vertexBuffer);

	glEnableVertexAttribArray(maTextureCoordHandle);
	glVertexAttribPointer(maTextureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, texCoordBuffer);



	// Connect the texture
	glActiveTexture(GL_TEXTURE0);
	// Bind the texture handle
    glBindTexture(GL_TEXTURE_2D, glTexture);
	// Set the sampler texture unit to 0
	glUniform1i(maTextureHandle, 0);

	// Send the modelViewProjection Matrix
	glUniformMatrix4fv(maMVPMatrixHandle, 1, false, modelViewProjectionMatrix);




}

void mjSkyboxShaders::RunForAssimp(const aiMesh* assimpMesh, mjModelMesh* mjMesh,
                                   float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
                                   float* modelMatrix, float* modelViewProjectionMatrix, int glTexture){

}

#ifdef USE_GLES2

	#include "gles2/skyboxShaderSources-gles2.h"

#else

	#include "gl3/skyboxShaderSources-gl3.h"

#endif


}
