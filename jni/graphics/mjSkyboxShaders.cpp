#include "mjSkyboxShaders.h"

namespace mjEngine{

mjSkyboxShaders::mjSkyboxShaders()
{
	// Set up shader
	CreateProgram(skyboxVertexShaderCode, skyboxFragmentShaderCode);
	name = new char[7];
	strncpy(name, "skybox", strnlen("skybox", 10)+1);
    LOGI("%s %d: new %s", __FILE__, __LINE__, "char[] for skybox shader name");

    checkGlError("create glProgram");

    // Get the texture handle location
    maTextureHandle = glGetUniformLocation(glProgramHandle, "uTexture");

    maMVPMatrixHandle = glGetUniformLocation(glProgramHandle, "maMVPMatrix");
    maMMatrixHandle = glGetUniformLocation(glProgramHandle, "maMMatrix");


    checkGlError("getting parameters");

    LOGI("textureHandle %d, mvpMAtrixHandle %d", maTextureHandle, maMVPMatrixHandle);

    enableDepthMask = false;
    enableDepthTest = false;

}


void mjSkyboxShaders::Run(mjModelMesh* mesh,
			float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
            float* modelMatrix, float* modelViewProjectionMatrix, int glTexture, float* extraColorForTexture)
{

    glUseProgram(glProgramHandle);


    // Send the modelViewProjection Matrix
    glUniformMatrix4fv(maMVPMatrixHandle, 1, false, modelViewProjectionMatrix);
    // Send the modelViewProjection Matrix
    glUniformMatrix4fv(maMMatrixHandle, 1, false, modelMatrix);

    // Connect the texture
    glActiveTexture(GL_TEXTURE0);
    // Bind the texture handle
    glBindTexture(GL_TEXTURE_2D, glTexture);
    // Set the sampler texture unit to 0
    glUniform1i(maTextureHandle, 0);




}

#ifdef USE_ASSIMP
void mjSkyboxShaders::RunForAssimp(const aiMesh* assimpMesh, mjModelMesh* mjMesh,
                                   float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
                                   float* modelMatrix, float* modelViewProjectionMatrix, int glTexture, ){

}
#endif // USE_ASSIMP

#ifdef USE_GLES2

	#include "gles2/skyboxShaderSources-gles2.h"

#else

	#include "gl3/skyboxShaderSources-gl3.h"

#endif


}
