#ifndef MJSCENEGRAPH_H
#define MJSCENEGRAPH_H

#include <vector>
#include "../core/mjObject.h"
namespace mjEngine
{

class mjSceneGraph
{
public:
	std::vector<mjObject*> drawableObjects;
	std::vector<mjObject*> shadowCasters;
};

}
#endif
