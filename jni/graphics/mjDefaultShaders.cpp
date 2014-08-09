
#include "mjDefaultShaders.h"



namespace mjEngine{

mjDefaultShaders::mjDefaultShaders()
{
	//Setup
	CreateProgram(simpleVertexShaderCode, simpleFragmentShaderCode);
	name = new char[8];
	strncpy(name, "default", 8);

	LOGI("Programhandle is %d", glProgramHandle);
	maPositionHandle = glGetAttribLocation(glProgramHandle, "vPosition");
	LOGI("Position : %d", maPositionHandle);
	//maNormalHandle = glGetAttribLocation(glProgram, "aNormal");

	maTextureCoordHandle = glGetAttribLocation(glProgramHandle, "aTexCoordinates");
	LOGI("texcoords: %d", maTextureCoordHandle);

	// Get the texture handle location
	maTextureHandle = glGetUniformLocation(glProgramHandle, "uTexture");

	maMVPMatrixHandle = glGetUniformLocation(glProgramHandle, "maMVPMatrix");
	LOGI("textureHAndle %d, mvpMAtrixHAndle %d", maTextureHandle, maMVPMatrixHandle);
}
void mjDefaultShaders::Run(mjModelMesh* mesh,
		float* vertexBuffer, float* texCoordBuffer, float* normalComponentBuffer,
		float* modelViewProjectionMatrix)
{
	 glUseProgram(glProgramHandle);
	 glEnableVertexAttribArray(maPositionHandle);
	 glVertexAttribPointer(maPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, vertexBuffer);

	 // Connect the texture
	 glActiveTexture(GL_TEXTURE0);
	 // Bind the texture handle
	 glBindTexture(GL_TEXTURE_2D, mesh->glTexture);
	 // Set the sampler texture unit to 0
	 glUniform1i(maTextureHandle, 0);


	 //Prepare ("connect") the triangle coordinate data
	 // Offset in the buffer, for accessing the texcoord data directly

	 glVertexAttribPointer(maTextureCoordHandle, 2,
			 GL_FLOAT, GL_FALSE,
			 0, texCoordBuffer);

	 // Enable a handle to the texture coordinates
	 glEnableVertexAttribArray(maTextureCoordHandle);

	 // Send the modelViewProjection Matrix
	 glUniformMatrix4fv(maMVPMatrixHandle, 1, false, modelViewProjectionMatrix);

}

const char* mjDefaultShaders::vanillaFragmentShaderCode =
		"precision mediump float;\n"

		 "varying vec2 vTexCoordinates;\n"
		 "uniform sampler2D uTexture;\n"

		 "varying vec4 vLight;\n"

		 "void main(){ \n"
		 " gl_FragColor = texture2D(uTexture, vTexCoordinates)* vLight;\n"
		 "} \n";




const char* mjDefaultShaders::vanillaVertexShaderCode =
			"attribute vec4 vPosition; \n"
	        "attribute vec2 aTexCoordinates;\n"
	        "attribute vec3 aNormal;\n"
	        "uniform mat4 uMVPMatrix;\n"

	        "uniform mat4 uMVMatrix;\n"
			"uniform vec4 uDiffuseLightColor;\n"

	        "uniform vec3 uDiffuseLightDirection;\n"

	        "uniform vec4 uAmbientLightColor;\n"

	        "varying vec2 vTexCoordinates;\n"
	        "varying vec4 vLight;\n"


	        "void main(){              \n"
	        " gl_Position = uMVPMatrix * vPosition; \n"
	        " vec3 mcNormal = aNormal;\n"

	        "   vTexCoordinates = aTexCoordinates;\n"

				// Calculate and normalize eye space normal
				// uMVMatrix = modelView matrix
				" vec3 ecNormal = vec3(uMVPMatrix * vec4(aNormal, 0.0));\n"
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
