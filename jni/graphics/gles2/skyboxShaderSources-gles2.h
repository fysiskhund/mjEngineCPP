
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