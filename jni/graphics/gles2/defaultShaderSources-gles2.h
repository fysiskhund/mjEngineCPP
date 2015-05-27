

//OpenGL ES 2.0 version of the sources to the default shaders


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
         "  if (gl_FragColor.a < 0.1)\n"
         "  {\n"
         "       discard;\n"
         "  }\n"
		 "} \n";


