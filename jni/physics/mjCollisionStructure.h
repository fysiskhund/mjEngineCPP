#ifndef MJCOLLISIONSTRUCTURE
#define MJCOLLISIONSTRUCTURE

namespace mjEngine{

enum structuretype
{
	MJ_UNDEFINED=0,
	MJ_SPHERE,
	MJ_AABB,
	MJ_TRIANGLE,
	MJ_TRIANGLE_MESH
};

class mjCollisionStructure
{
public:
	structuretype type;
};

}


#endif
