

const char* mjSkyboxShaders::skyboxVertexShaderCode =
        "#version 330 core \n"

        "layout(location = 0) in vec3 MJ_VERTEX_COORDINATES; \n"
        "layout(location = 1) in vec3 MJ_NORMAL_COORDINATES;\n"
        "layout(location = 3) in vec2 MJ_UV_COMPONENTS;\n"
        "uniform mat4 maMVPMatrix;\n"

        "uniform mat4 maMMatrix;\n"

        "out vec2 textureCoordinatesForFragmentShader;\n"


        "void main(){              \n"

        " gl_Position = maMVPMatrix * vec4(MJ_VERTEX_COORDINATES, 1); \n"

        " textureCoordinatesForFragmentShader = MJ_UV_COMPONENTS;\n"

        "} \n";


const char* mjSkyboxShaders::skyboxFragmentShaderCode =

        "#version 330 core \n"
         //"precision mediump float;\n"

         "in vec2 textureCoordinatesForFragmentShader;\n"
         "uniform sampler2D uTexture;\n"

         "out vec4 fragColorOut;\n"

         "void main(){ \n"
        //"gl_FragColor = vec4(0,1,0,1)*lightParameterForFragmentShader; \n"
         " fragColorOut = texture(uTexture, textureCoordinatesForFragmentShader);\n"
         "} \n";
