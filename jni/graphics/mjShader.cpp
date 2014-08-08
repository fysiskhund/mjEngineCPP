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
				/*char* buf = (char*) malloc(infoLen);
				if (buf) {
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
					//LOGE("Could not compile shader %d:\n%s\n",
					//		shaderType, buf);
					free(buf);
				}*/
				glDeleteShader(shader);
				shader = 0;
			}
		}
	}
	return shader;
}

void mjShader::CreateProgram(const char* vertexShaderCode, const char* fragmentShaderCode)
{
	glVertexShaderHandle = LoadShader(GL_VERTEX_SHADER, vertexShaderCode);
	glFragmentShaderHandle = LoadShader(GL_FRAGMENT_SHADER, vertexShaderCode);

	GLuint glProgramHandle = glCreateProgram();
	if (glProgramHandle) {
		glAttachShader(glProgramHandle, glVertexShaderHandle);
		//checkGlError("glAttachShader");
		glAttachShader(glProgramHandle, glFragmentShaderHandle);
		//checkGlError("glAttachShader");
		glLinkProgram(glProgramHandle);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(glProgramHandle, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint bufLength = 0;
			glGetProgramiv(glProgramHandle, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength) {
				/*char* buf = (char*) malloc(bufLength);
				if (buf) {
					glGetProgramInfoLog(glProgramHandle, bufLength, NULL, buf);
					//LOGE("Could not link program:\n%s\n", buf);
					free(buf);
				}*/
			}
			glDeleteProgram(glProgramHandle);
			glProgramHandle = 0;
		}
	}
}

}
