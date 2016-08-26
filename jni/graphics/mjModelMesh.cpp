#include "mjModelMesh.h"



namespace mjEngine{

mjModelMesh::mjModelMesh()
{
    checkGlError("first line of mesh creation");
	drawOrderCount = -1;
    glGenBuffers(1, &elementBufferID);

    checkGlError("mesh creation");

}
    
    
}// namespace mjEngine
