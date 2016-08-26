
#include "mjDefaultShaders.h"



namespace mjEngine{

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
	strncpy(name, "default", 8);

    checkGlError("create glProgram");


	/*LOGI("Programhandle is %d", glProgramHandle);
	maPositionHandle = glGetAttribLocation(glProgramHandle, "vPosition");

	maNormalHandle = glGetAttribLocation(glProgramHandle, "aNormal");

	LOGI("Position : %d", maPositionHandle);
	//maNormalHandle = glGetAttribLocation(glProgram, "aNormal");

	maTextureCoordHandle = glGetAttribLocation(glProgramHandle, "aTexCoordinates");
	LOGI("texcoords: %d", maTextureCoordHandle); */

	// Get the texture handle location
    maTextureHandle = glGetUniformLocation(glProgramHandle, "uTexture");

	maMVPMatrixHandle = glGetUniformLocation(glProgramHandle, "maMVPMatrix");
	maMMatrixHandle = glGetUniformLocation(glProgramHandle, "maMMatrix");

	uDiffuseLightDirectionHandle = glGetUniformLocation(glProgramHandle, "uDiffuseLightDirection");
	uDiffuseLightColorHandle = glGetUniformLocation(glProgramHandle, "uDiffuseLightColor");

	uAmbientLightColorHandle = glGetUniformLocation(glProgramHandle, "uAmbientLightColor");
    checkGlError("getting parameters");

    LOGI("textureHandle %d, mvpMAtrixHandle %d", maTextureHandle, maMVPMatrixHandle);
}

void mjDefaultShaders::Run(mjModelMesh* mesh,
		float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
        float* modelMatrix, float* modelViewProjectionMatrix, int glTexture)
{
	 glUseProgram(glProgramHandle);


     // Send the light parameters
     glUniform3fv(uDiffuseLightDirectionHandle, 1, diffuseLightDirectionArray);
     glUniform4fv(uDiffuseLightColorHandle, 1, diffuseLightColor);
     glUniform4fv(uAmbientLightColorHandle, 1, ambientLightColor);

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


#ifdef USE_GLES2

	#include "gles2/defaultShaderSources-gles2.h"

#else

	#include "gl3/defaultShaderSources-gl3.h"

#endif

const char* mjDefaultShaders::simpleVertexShaderCode =
		"attribute vec4 vPosition;\n"
		"attribute vec2 aTexCoordinates;\n"
		"uniform mat4 maMVPMatrix;\n"

		"varying vec2 vTexCoordinates;\n"
	    "void main() {\n"
	    "  gl_Position = maMVPMatrix*vPosition;\n"
		"  vTexCoordinates = aTexCoordinates;\n"
	    "}\n";

const char* mjDefaultShaders::simpleFragmentShaderCode =
		"precision mediump float;\n"
		"varying vec2 vTexCoordinates;\n"
		"uniform sampler2D uTexture;\n"
	    "void main() {\n"
	    "  gl_FragColor = texture2D(uTexture, vTexCoordinates);\n"
	    "}\n";

}
