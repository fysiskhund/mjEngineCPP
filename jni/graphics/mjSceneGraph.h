#ifndef MJSCENEGRAPH_H
#define MJSCENEGRAPH_H

#include <vector>
#include <algorithm>    // std::sort
#include "../core/mjObject.h"
#include "../graphics/mjShader.h"
#include "../graphics/mjCamera.h"
#include "../extLibs/math/mjMatrixStack.h"
#include "../extLibs/math/Matrix.h"

namespace mjEngine
{

class mjSceneGraph
{
public:
    bool sortTranslucentObjects = true;
	std::vector<mjObject*> drawableObjects;
	std::vector<mjObject*> translucentObjects;
	std::vector<mjObject*> shadowCasters;

    mjMatrixStack matrixStack;

	void Update(float t_elapsed);
	void Draw(mjCamera* camera, std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix);
private:
    static bool SortByInvDistanceToCamera(mjObject* obj0,mjObject* obj1);

};

}
#endif
