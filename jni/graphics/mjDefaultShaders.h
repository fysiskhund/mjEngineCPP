#ifndef MJDEFAULTSHADERS
#define MJDEFAULTSHADERS

#include "mjShader.h"

namespace mjEngine{

class mjDefaultShaders:  public mjShader
{
	public:
	mjDefaultShaders();
	void Run(mjModelMesh* mesh) override;
	static const char* simpleVertexShaderCode;
	static const char* simpleFragmentShaderCode;
	static const char* vanillaVertexShaderCode;
	static const char* vanillaFragmentShaderCode;

};
}
#endif
