#ifndef MJMODELMESH_H
#define MJMODELMESH_H
namespace mjEngine{
class mjModelMesh
{
public:
	char* name;
	char* material;
	unsigned short* drawOrderBuffer;
	unsigned int drawOrderCount;

	mjModelMesh();
};
}// namespace mjEngine
#endif
