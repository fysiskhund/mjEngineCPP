#ifndef MJCOLLISIONSTRUCTURE
#define MJCOLLISIONSTRUCTURE

namespace mjEngine{

enum structuretype
{
	MJ_SPHERE,
	MJ_AABB,
	MJ_TRIANGLE,
	MJ_TRIANGLE_MESH
};

class mjBoundingStructure
{
public:
	structuretype type;
	bool isImmovable = false;
};

}


#endif
