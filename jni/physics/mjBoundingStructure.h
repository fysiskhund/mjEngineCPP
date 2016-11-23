#ifndef MJCOLLISIONSTRUCTURE
#define MJCOLLISIONSTRUCTURE

namespace mjEngine{

enum structuretype
{
	MJ_SPHERE,
	MJ_AABB,
	MJ_TRIANGLE,
    MJ_TRIANGLE_MESH,
    MJ_NO_BOUNDING_STRUCT
};

class mjBoundingStructure
{
public:
	structuretype type;
	bool isImmovable = false;
};

}


#endif
