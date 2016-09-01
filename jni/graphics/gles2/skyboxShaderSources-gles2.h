
const char* mjSkyboxShaders::skyboxVertexShaderCode =
        "attribute vec4 MJ_VERTEX_COORDINATES; \n"
        "attribute vec2 MJ_UV_COMPONENTS;\n"
        "uniform mat4 maMVPMatrix;\n"

        "varying vec2 textureCoordinatesForFragmentShader;\n"

	    "void main() {\n"
	    "  gl_Position = maMVPMatrix*MJ_VERTEX_COORDINATES;\n"
		"  textureCoordinatesForFragmentShader = MJ_UV_COMPONENTS;\n"
	    "}\n";

const char* mjSkyboxShaders::skyboxFragmentShaderCode =
		"precision mediump float;\n"
		"varying vec2 textureCoordinatesForFragmentShader;\n"
		"uniform sampler2D uTexture;\n"
	    "void main() {\n"
	    "  gl_FragColor = texture2D(uTexture, textureCoordinatesForFragmentShader);\n"
	    "}\n";