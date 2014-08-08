#ifndef MJSHADER
#define MJSHADER

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "mjModelMesh.h"

namespace mjEngine
{

class mjShader{
public:
	GLuint glProgramHandle;
	GLuint glVertexShaderHandle;
	GLuint glFragmentShaderHandle;
	virtual void Run(mjModelMesh*){}; // Gets called before drawing something
	GLuint LoadShader(GLenum shaderType, const char* pSource);
	void CreateProgram(const char* vertexShadercode, const char* fragmentShaderCode);
};

}

#endif
