
#include "mjDefaultShaders.h"



namespace mjEngine{

mjDefaultShaders::mjDefaultShaders()
{
	//Set up lights

	diffuseLightDirection.Set(0.2, 1, -0.2);
	diffuseLightDirection.Normalize();
	diffuseLightDirection.CopyToArray(diffuseLightDirectionArray);

	diffuseLightColor[0] = diffuseLightColor[1] = diffuseLightColor[2] = 0.9;
	diffuseLightColor[3] = 1;

	ambientLightColor[0] = ambientLightColor[1] = ambientLightColor[2] = 0.5;
	ambientLightColor[3] = 1;



	// Set up shader
	CreateProgram(vanillaVertexShaderCode, vanillaFragmentShaderCode);
	name = new char[8];
	strncpy(name, "default", 8);

	LOGI("Programhandle is %d", glProgramHandle);
	maPositionHandle = glGetAttribLocation(glProgramHandle, "vPosition");

	maNormalHandle = glGetAttribLocation(glProgramHandle, "aNormal");

	LOGI("Position : %d", maPositionHandle);
	//maNormalHandle = glGetAttribLocation(glProgram, "aNormal");

	maTextureCoordHandle = glGetAttribLocation(glProgramHandle, "aTexCoordinates");
	LOGI("texcoords: %d", maTextureCoordHandle);

	// Get the texture handle location
	maTextureHandle = glGetUniformLocation(glProgramHandle, "uTexture");

	maMVPMatrixHandle = glGetUniformLocation(glProgramHandle, "maMVPMatrix");
	maMMatrixHandle = glGetUniformLocation(glProgramHandle, "maMMatrix");

	uDiffuseLightDirectionHandle = glGetUniformLocation(glProgramHandle, "uDiffuseLightDirection");
	uDiffuseLightColorHandle = glGetUniformLocation(glProgramHandle, "uDiffuseLightColor");

	uAmbientLightColorHandle = glGetUniformLocation(glProgramHandle, "uAmbientLightColor");

	LOGI("textureHAndle %d, mvpMAtrixHAndle %d", maTextureHandle, maMVPMatrixHandle);
}
void mjDefaultShaders::Run(mjModelMesh* mesh,
		float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
		float* modelMatrix, float* modelViewProjectionMatrix)
{
	 glUseProgram(glProgramHandle);
	 glEnableVertexAttribArray(maPositionHandle);
	 glVertexAttribPointer(maPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, vertexBuffer);

	 glEnableVertexAttribArray(maNormalHandle);
	 glVertexAttribPointer(maNormalHandle, 3, GL_FLOAT, GL_FALSE, 0, normalComponentBuffer);

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
	 // Send the modelViewProjection Matrix
	 glUniformMatrix4fv(maMMatrixHandle, 1, false, modelMatrix);

	 // Send the light parameters
	 glUniform3fv(uDiffuseLightDirectionHandle, 1, diffuseLightDirectionArray);
	 glUniform4fv(uDiffuseLightColorHandle, 1, diffuseLightColor);
	 glUniform4fv(uAmbientLightColorHandle, 1, ambientLightColor);
}






const char* mjDefaultShaders::vanillaVertexShaderCode =
			"attribute vec4 vPosition; \n"
	        "attribute vec2 aTexCoordinates;\n"
	        "attribute vec3 aNormal;\n"
	        "uniform mat4 maMVPMatrix;\n"

	        "uniform mat4 maMMatrix;\n"
			"uniform vec4 uDiffuseLightColor;\n"

	        "uniform vec3 uDiffuseLightDirection;\n"

	        "uniform vec4 uAmbientLightColor;\n"

	        "varying vec2 vTexCoordinates;\n"
	        "varying vec4 vLight;\n"


	        "void main(){              \n"
	        " gl_Position = maMVPMatrix * vPosition; \n"
	        " vec3 mcNormal = aNormal;\n"

	        "   vTexCoordinates = aTexCoordinates;\n"

				// Calculate and normalize eye space normal
				// maMVMatrix = modelView matrix
				" vec3 ecNormal = vec3(maMMatrix * vec4(aNormal, 0.0));\n"
			    " ecNormal = ecNormal / length(ecNormal);\n"

			    " float ecNormalDotLightDirection = max(0.0, dot(ecNormal, uDiffuseLightDirection));\n"

	        //Diffuse light calculation
	        " vec4 diffuseLight = uAmbientLightColor + (ecNormalDotLightDirection * uDiffuseLightColor);\n"

	        /*
	         //Debugging code :P
	         " vec4 diffColour = vec4(1, 1, 1, 1); \n"+
	        " if (aNormal.x == 0.0) { \n"+
	        "  diffColour.x = 0.0; \n" +
	        " } \n" +
	        " if (aNormal.y == 0.0) { \n"+
	        "  diffColour.y = 0.0; \n" +
	        " } \n" +
	        " if (aNormal.z == 0.0) { \n"+
	        "  diffColour.z = 0.0; \n" +
	        " } \n" +*/
	        " vLight = diffuseLight + vec4(0,0,0,1); \n"  // diffuseLight;\n"+ // plus reflective component plus ambient light

	        "} \n";

const char* mjDefaultShaders::vanillaFragmentShaderCode =
		"precision mediump float;\n"

		 "varying vec2 vTexCoordinates;\n"
		 "uniform sampler2D uTexture;\n"

		 "varying vec4 vLight;\n"

		 "void main(){ \n"
		//"gl_FragColor = vec4(0,1,0,1)*vLight; \n"
		 " gl_FragColor = texture2D(uTexture, vTexCoordinates)* vLight;\n"
		 "} \n";


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
