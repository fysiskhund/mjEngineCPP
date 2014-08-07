#ifndef MJDEFAULTSHADERS
#define MJDEFAULTSHADERS

#include "mjShader.h"

namespace mjEngine{

class mjDefaultShaders:  public mjShader
{
	public:
	mjDefaultShaders();
	const char* vanillaVertexShaderCode;
	const char* vanillaFragmentShaderCode;

};
}
#endif
