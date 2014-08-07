#include "mjModelMesh.h"

namespace mjEngine{

mjModelMesh::mjModelMesh()
{

}

void mjModelMesh::Draw()
{

	if (shader == null)
	{
		mjDefaultShaders defShaders;
		glUseProgram(shader->show);
	}
}
}// namespace mjEngine
