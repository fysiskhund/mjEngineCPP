

// OpenGL ES 2.0 version of the sources to the default shaders


const char* mjTextShaders::vertexShaderCode =
                "attribute vec3 MJ_VERTEX_COORDINATES; \n"
	        "attribute vec2 MJ_UV_COMPONENTS;\n"
	        "uniform mat4 maMVPMatrix;\n"

	        "varying vec2 textureCoordinatesForFragmentShader;\n"



	        "void main(){              \n"
                " gl_Position = maMVPMatrix * vec4(MJ_VERTEX_COORDINATES, 1); \n"

	        "   textureCoordinatesForFragmentShader = MJ_UV_COMPONENTS;\n"

	        "} \n";

const char* mjTextShaders::fragmentShaderCode =
		 "precision mediump float;\n"

		 "varying vec2 textureCoordinatesForFragmentShader;\n"
		 "uniform sampler2D uTexture;\n"
                 "uniform vec4 uExtraColorForTexture;\n"

		 "void main(){ \n"
                 " gl_FragColor = vec4(uExtraColorForTexture.r, uExtraColorForTexture.g, uExtraColorForTexture.b, texture2D(uTexture, textureCoordinatesForFragmentShader).r);\n"
         "  if (gl_FragColor.a < 0.1)\n"
         "  {\n"
         "       discard;\n"
         "  }\n"
		 "} \n";


