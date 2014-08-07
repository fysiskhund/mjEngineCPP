#ifndef MJMODELMESH_H
#define MJMODELMESH_H

#include "mjShader.h"

namespace mjEngine{
class mjModelMesh
{
public:
	char* name;
	char* material;
	unsigned short* drawOrderBuffer;
	unsigned int drawOrderCount;

	mjShader* shader;

	mjModelMesh();

	void Draw();

};
}// namespace mjEngine
#endif
