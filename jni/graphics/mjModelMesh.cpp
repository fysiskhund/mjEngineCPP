#include "mjModelMesh.h"



namespace mjEngine{

mjModelMesh::mjModelMesh()
{
    checkGlError("first line of mesh creation");
	drawOrderCount = -1;
    glGenBuffers(1, &elementBufferID);
    LOGI("%s %d: new %s", __FILE__, __LINE__, "glGenBuffers");

    checkGlError("mesh creation");

}
    
    
}// namespace mjEngine
