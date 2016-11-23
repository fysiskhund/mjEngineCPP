
#include "mjDefaultShaders.h"



namespace mjEngine{

#ifdef USE_GLES2

    #include "gles2/defaultShaderSources-gles2.h"

#else

    #include "gl3/defaultShaderSources-gl3.h"

#endif

mjDefaultShaders::mjDefaultShaders()
{
	//Set up lights

	diffuseLightDirection.Set(0.5, 1, -0.2);
	diffuseLightDirection.Normalize();
	diffuseLightDirection.CopyToArray(diffuseLightDirectionArray);

	diffuseLightColor[0] = diffuseLightColor[1] = diffuseLightColor[2] = 0.8;
	diffuseLightColor[3] = 1;

	ambientLightColor[0] = ambientLightColor[1] = ambientLightColor[2] = 0.69;
	ambientLightColor[3] = 1;

    checkGlError("set up lights");


	// Set up shader
	CreateProgram(vanillaVertexShaderCode, vanillaFragmentShaderCode);//vanillaFragmentShaderCode_GL3_3);//
	name = new char[8];
    LOGI("%s %d: new %s", __FILE__, __LINE__, "char[] for shaderName");

	strncpy(name, "default", 8);

    checkGlError("create glProgram");

	// Get the texture handle location
    maTextureHandle = glGetUniformLocation(glProgramHandle, "uTexture");

	maMVPMatrixHandle = glGetUniformLocation(glProgramHandle, "maMVPMatrix");
	maMMatrixHandle = glGetUniformLocation(glProgramHandle, "maMMatrix");

	uDiffuseLightDirectionHandle = glGetUniformLocation(glProgramHandle, "uDiffuseLightDirection");
	uDiffuseLightColorHandle = glGetUniformLocation(glProgramHandle, "uDiffuseLightColor");

	uAmbientLightColorHandle = glGetUniformLocation(glProgramHandle, "uAmbientLightColor");
    uExtraColorForTextureHandle = glGetUniformLocation(glProgramHandle, "uExtraColorForTexture");
    checkGlError("getting parameters");

    LOGI("textureHandle %d, mvpMAtrixHandle %d", maTextureHandle, maMVPMatrixHandle);
}

void mjDefaultShaders::Run(mjModelMesh* mesh,
		float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
        float* modelMatrix, float* modelViewProjectionMatrix, int glTexture, float* extraColorForTexture)
{
	 glUseProgram(glProgramHandle);


     // Send the light parameters
     glUniform3fv(uDiffuseLightDirectionHandle, 1, diffuseLightDirectionArray);
     glUniform4fv(uDiffuseLightColorHandle, 1, diffuseLightColor);
     glUniform4fv(uAmbientLightColorHandle, 1, ambientLightColor);
     glUniform4fv(uExtraColorForTextureHandle, 1, extraColorForTexture);

     // Send the modelViewProjection Matrix
     glUniformMatrix4fv(maMVPMatrixHandle, 1, false, modelViewProjectionMatrix);
     // Send the modelView Matrix
     glUniformMatrix4fv(maMMatrixHandle, 1, false, modelMatrix);

	 // Connect the texture
	 glActiveTexture(GL_TEXTURE0);
	 // Bind the texture handle
     glBindTexture(GL_TEXTURE_2D, glTexture);
	 // Set the sampler texture unit to 0
	 glUniform1i(maTextureHandle, 0);




}

#ifdef USE_ASSIMP

void mjDefaultShaders::RunForAssimp(const aiMesh* assimpMesh, mjModelMesh* mjMesh,
                                    float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
                                    float* modelMatrix, float* modelViewProjectionMatrix, int glTexture)
{
     glUseProgram(glProgramHandle);
     glEnableVertexAttribArray(maPositionHandle);
     glVertexAttribPointer(maPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, vertexBuffer); // vertexBuffer

     glEnableVertexAttribArray(maNormalHandle);
     glVertexAttribPointer(maNormalHandle, 3, GL_FLOAT, GL_FALSE, 0, normalComponentBuffer); // normalComponentBuffer

     glEnableVertexAttribArray(maTextureCoordHandle);
     glVertexAttribPointer(maTextureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, texCoordBuffer); // texCoordBuffer



     // Connect the texture
     glActiveTexture(GL_TEXTURE0);
     // Bind the texture handle
     glBindTexture(GL_TEXTURE_2D, glTexture);
     // Set the sampler texture unit to 0
     glUniform1i(maTextureHandle, 0);

     // Send the modelViewProjection Matrix
     glUniformMatrix4fv(maMVPMatrixHandle, 1, false, modelViewProjectionMatrix);
     // Send the model Matrix
     glUniformMatrix4fv(maMMatrixHandle, 1, false, modelMatrix);

     // Send the light parameters
     glUniform3fv(uDiffuseLightDirectionHandle, 1, diffuseLightDirectionArray);
     glUniform4fv(uDiffuseLightColorHandle, 1, diffuseLightColor);
     glUniform4fv(uAmbientLightColorHandle, 1, ambientLightColor);
     checkGlError("runForAssimp");
}

#endif





}
