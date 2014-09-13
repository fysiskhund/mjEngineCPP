#include "mjSkyboxShaders.h"

namespace mjEngine{

mjSkyboxShaders::mjSkyboxShaders()
{
	// Set up shader
	CreateProgram(skyboxVertexShaderCode, skyboxFragmentShaderCode);
	name = new char[7];
	strncpy(name, "skybox", strnlen("skybox", 10));

	maPositionHandle = glGetAttribLocation(glProgramHandle, "vPosition");



	maTextureCoordHandle = glGetAttribLocation(glProgramHandle, "aTexCoordinates");

	// Get the texture handle location
	maTextureHandle = glGetUniformLocation(glProgramHandle, "uTexture");

	maMVPMatrixHandle = glGetUniformLocation(glProgramHandle, "maMVPMatrix");

}


void mjSkyboxShaders::Run(mjModelMesh* mesh,
			float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
			float* modelMatrix, float* modelViewProjectionMatrix )
{

	glUseProgram(glProgramHandle);
	glEnableVertexAttribArray(maPositionHandle);
	glVertexAttribPointer(maPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, vertexBuffer);

	glEnableVertexAttribArray(maTextureCoordHandle);
	glVertexAttribPointer(maTextureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, texCoordBuffer);



	// Connect the texture
	glActiveTexture(GL_TEXTURE0);
	// Bind the texture handle
	glBindTexture(GL_TEXTURE_2D, mesh->glTexture);
	// Set the sampler texture unit to 0
	glUniform1i(maTextureHandle, 0);

	// Send the modelViewProjection Matrix
	glUniformMatrix4fv(maMVPMatrixHandle, 1, false, modelViewProjectionMatrix);




}


const char* mjSkyboxShaders::skyboxVertexShaderCode =
		"attribute vec4 vPosition;\n"
		"attribute vec2 aTexCoordinates;\n"
		"uniform mat4 maMVPMatrix;\n"

		"varying vec2 vTexCoordinates;\n"
	    "void main() {\n"
	    "  gl_Position = maMVPMatrix*vPosition;\n"
		"  vTexCoordinates = aTexCoordinates;\n"
	    "}\n";

const char* mjSkyboxShaders::skyboxFragmentShaderCode =
		"precision mediump float;\n"
		"varying vec2 vTexCoordinates;\n"
		"uniform sampler2D uTexture;\n"
	    "void main() {\n"
	    "  gl_FragColor = texture2D(uTexture, vTexCoordinates);\n"
	    "}\n";


}
