

const char* mjSkyboxShaders::skyboxVertexShaderCode =
#ifdef OSX
// "I'm different!!!!!!!!!!!!!!!!!!!!!111 LOOK AT ME!!! OMG!!" ¬¬
		"#version 150 \n"
#else
		"#version 130 \n"
#endif

		"in vec4 vPosition;\n"
		"in vec2 aTexCoordinates;\n"
		"uniform mat4 maMVPMatrix;\n"

		"out vec2 vTexCoordinates;\n"
	    "void main() {\n"
	    "  gl_Position = maMVPMatrix*vPosition;\n"
		"  vTexCoordinates = aTexCoordinates;\n"
	    "}\n";

const char* mjSkyboxShaders::skyboxFragmentShaderCode =
#ifdef OSX
// "I'm different!!!!!!!!!!!!!!!!!!!!!111 LOOK AT ME!!! OMG!!" ¬¬
		"#version 150 \n"
#else
		"#version 130 \n"
#endif
		//"precision mediump float;\n" does this exist in GL3?
		"in vec2 vTexCoordinates;\n"
		"uniform sampler2D uTexture;\n"
        "out vec4 fragColorOut;\n"
	    "void main() {\n"
	    "  fragColorOut = texture(uTexture, vTexCoordinates);\n"
	    "}\n";
