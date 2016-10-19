

//OpenGL 3.3 version of the sources to the default shaders


const char* mjTextShaders::vertexShaderCode =

            "#version 330 core \n"

            "layout(location = 0) in vec3 MJ_VERTEX_COORDINATES; \n"
            "layout(location = 3) in vec2 MJ_UV_COMPONENTS;\n"
	        "uniform mat4 maMVPMatrix;\n"

	        "out vec2 textureCoordinatesForFragmentShader;\n"

	        "void main(){              \n"

                    " gl_Position = maMVPMatrix * vec4(MJ_VERTEX_COORDINATES, 1); \n"

                    " textureCoordinatesForFragmentShader = MJ_UV_COMPONENTS;\n"

	        "} \n";

const char* mjTextShaders::fragmentShaderCode =
        "#version 330 core \n"
		 //"precision mediump float;\n"

         "uniform vec4 uExtraColorForTexture;\n"
		 "uniform sampler2D uTexture;\n"

         "in vec2 textureCoordinatesForFragmentShader;\n"

         "out vec4 fragColorOut;\n"

		 "void main(){ \n"


         " fragColorOut = vec4(uExtraColorForTexture.r, uExtraColorForTexture.g, uExtraColorForTexture.b, texture(uTexture, textureCoordinatesForFragmentShader).r);\n"
         "  if (fragColorOut.a < 0.1)\n"
         "  {\n"
         "       discard;\n"
         "  }\n"
         "} \n";


