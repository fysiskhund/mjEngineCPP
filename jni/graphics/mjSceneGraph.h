#ifndef MJSCENEGRAPH_H
#define MJSCENEGRAPH_H

#include <vector>
#include "../core/mjObject.h"
#include "../graphics/mjShader.h"

namespace mjEngine
{

class mjSceneGraph
{
public:
	std::vector<mjObject*> drawableObjects;
	std::vector<mjObject*> translucentObjects;
	std::vector<mjObject*> shadowCasters;

	void Update(float t_elapsed);
	void Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix);
};

}
#endif
