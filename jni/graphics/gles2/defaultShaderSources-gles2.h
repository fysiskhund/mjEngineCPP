

//OpenGL ES 2.0 version of the sources to the default shaders


const char* mjDefaultShaders::vanillaVertexShaderCode =
			"attribute vec4 MJ_VERTEX_COORDINATES; \n"
	        "attribute vec2 MJ_UV_COMPONENTS;\n"
	        "attribute vec3 MJ_NORMAL_COORDINATES;\n"
	        "uniform mat4 maMVPMatrix;\n"

	        "uniform mat4 maMMatrix;\n"
			"uniform vec4 uDiffuseLightColor;\n"

	        "uniform vec3 uDiffuseLightDirection;\n"

	        "uniform vec4 uAmbientLightColor;\n"

	        "varying vec2 textureCoordinatesForFragmentShader;\n"
	        "varying vec4 lightParameterForFragmentShader;\n"


	        "void main(){              \n"
	        " gl_Position = maMVPMatrix * MJ_VERTEX_COORDINATES; \n"
	        " vec3 mcNormal = MJ_NORMAL_COORDINATES;\n"

	        "   textureCoordinatesForFragmentShader = MJ_UV_COMPONENTS;\n"

				// Calculate and normalize eye space normal
				// maMVMatrix = modelView matrix
				" vec3 ecNormal = vec3(maMMatrix * vec4(MJ_NORMAL_COORDINATES, 0.0));\n"
			    " ecNormal = ecNormal / length(ecNormal);\n"

			    " float ecNormalDotLightDirection = max(0.0, dot(ecNormal, uDiffuseLightDirection));\n"

	        //Diffuse light calculation
	        " vec4 diffuseLight = uAmbientLightColor + (ecNormalDotLightDirection * uDiffuseLightColor);\n"

	        /*
	         //Debugging code :P
	         " vec4 diffColour = vec4(1, 1, 1, 1); \n"+
	        " if (MJ_NORMAL_COORDINATES.x == 0.0) { \n"+
	        "  diffColour.x = 0.0; \n" +
	        " } \n" +
	        " if (MJ_NORMAL_COORDINATES.y == 0.0) { \n"+
	        "  diffColour.y = 0.0; \n" +
	        " } \n" +
	        " if (MJ_NORMAL_COORDINATES.z == 0.0) { \n"+
	        "  diffColour.z = 0.0; \n" +
	        " } \n" +*/
	        " lightParameterForFragmentShader = diffuseLight + vec4(0,0,0,1); \n"  // diffuseLight;\n"+ // plus reflective component plus ambient light

	        "} \n";

const char* mjDefaultShaders::vanillaFragmentShaderCode =
		 "precision mediump float;\n"

		 "varying vec2 textureCoordinatesForFragmentShader;\n"
		 "uniform sampler2D uTexture;\n"

		 "varying vec4 lightParameterForFragmentShader;\n"

		 "void main(){ \n"
		//"gl_FragColor = vec4(0,1,0,1)*lightParameterForFragmentShader; \n"
		 " gl_FragColor = texture2D(uTexture, textureCoordinatesForFragmentShader)* lightParameterForFragmentShader;\n"
         "  if (gl_FragColor.a < 0.1)\n"
         "  {\n"
         "       discard;\n"
         "  }\n"
		 "} \n";


