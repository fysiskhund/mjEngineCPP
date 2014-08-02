
#include "mjDefaultShaders.h"

namespace mjEngine{

mjDefaultShaders::mjDefaultShaders()
{
	//

	vanillaVertexShaderCode = 
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


	vanillaFragmentShaderCode =
				 "precision mediump float;\n"

				 "varying vec2 vTexCoordinates;\n"
				 "uniform sampler2D uTexture;\n"

				 "varying vec4 vLight;\n"

				 "void main(){ \n"
				 " gl_FragColor = texture2D(uTexture, vTexCoordinates)* vLight;\n"
				 "} \n";

}

}
