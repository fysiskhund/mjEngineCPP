#include "mjShader.h"

namespace mjEngine{

GLuint mjShader::LoadShader(GLenum shaderType, const char* pSource)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader) {
		glShaderSource(shader, 1, &pSource, NULL);
		glCompileShader(shader);
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen) {
				char* buf = (char*) malloc(infoLen);
				if (buf) {
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
					LOGI("Could not compile shader %d:\n%s\n",
							shaderType, buf);
					free(buf);
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	}
	return shader;
}

void mjShader::CreateProgram(const char* vertexShaderCode, const char* fragmentShaderCode)
{
	glProgramHandle = glCreateProgram();


	glVertexShaderHandle = LoadShader(GL_VERTEX_SHADER, vertexShaderCode);
	glFragmentShaderHandle = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

	//LOGI("vxshaderHandle %d, fragShaderHAndle: %d", glVertexShaderHandle, glFragmentShaderHandle);

	if (glProgramHandle) {
		//LOGI("VertexShader");
		glAttachShader(glProgramHandle, glVertexShaderHandle);
		//checkGlError("glAttachShader");
		//LOGI("fragmentShader");
		glAttachShader(glProgramHandle, glFragmentShaderHandle);

        BindAttributeLocations();

        //checkGlError("glAttachShader");
		glLinkProgram(glProgramHandle);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(glProgramHandle, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint bufLength = 0;
			glGetProgramiv(glProgramHandle, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength) {
				char* buf = (char*) malloc(bufLength);
				if (buf) {
					glGetProgramInfoLog(glProgramHandle, bufLength, NULL, buf);
					LOGI("Could not link program %d:\n%s\n", glProgramHandle, buf);
					free(buf);
				}
			}
			//LOGI("At glDeleteProgram :(");
			glDeleteProgram(glProgramHandle);
			glProgramHandle = 0;
		}
	}
}
void mjShader::BindAttributeLocations()
{
#ifdef USE_GLES2
    glBindAttribLocation(glProgramHandle, MJ_VERTEX_COORDINATES_GLVERTEXATTRIB_ID, "MJ_VERTEX_COORDINATES");
    glBindAttribLocation(glProgramHandle, MJ_NORMAL_COORDINATES_GLVERTEXATTRIB_ID, "MJ_NORMAL_COORDINATES");
    glBindAttribLocation(glProgramHandle, MJ_UV_COMPONENTS_GLVERTEXATTRIB_ID, "MJ_UV_COMPONENTS");
#endif
    
}

}
