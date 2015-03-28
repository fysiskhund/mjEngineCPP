

const char* mjSkyboxShaders::skyboxVertexShaderCode =
		"#version 330 \n"
		
		"in vec4 vPosition;\n"
		"in vec2 aTexCoordinates;\n"
		"uniform mat4 maMVPMatrix;\n"

		"out vec2 vTexCoordinates;\n"
	    "void main() {\n"
	    "  gl_Position = maMVPMatrix*vPosition;\n"
		"  vTexCoordinates = aTexCoordinates;\n"
	    "}\n";

const char* mjSkyboxShaders::skyboxFragmentShaderCode =
		//"precision mediump float;\n" does this exist in GL3?
		"in vec2 vTexCoordinates;\n"
		"uniform sampler2D uTexture;\n"
	    "void main() {\n"
	    "  gl_FragColor = texture2D(uTexture, vTexCoordinates);\n"
	    "}\n";