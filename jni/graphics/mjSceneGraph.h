#ifndef MJSCENEGRAPH_H
#define MJSCENEGRAPH_H

#include <vector>
#include <algorithm>    // std::sort
#include <core/mjObject.h>
#include <graphics/mjShader.h>
#include <graphics/mjCamera.h>
#include <extLibs/math/mjMatrixStack.h>
#include <extLibs/math/Matrix.h>
#include <graphics/renderer/mjRenderer.h>
#include <util/mjResourceManager.h>

#if defined(USE_GL3) || defined(USE_GLES2)
#include <graphics/renderer/mjRendererGL.h>

#endif

namespace mjEngine
{

class mjSceneGraph
{
public:

#if defined(USE_GL3) || defined(USE_GLES2)
    mjRendererGL renderer;
#else
    mjRenderer renderer;
#endif

    bool sortTranslucentObjects = true;
    std::vector<mjObject*> drawableObjects;
	std::vector<mjObject*> translucentObjects;
	std::vector<mjObject*> shadowCasters;

    mjMatrixStack matrixStack;

    void Initialize(mjResourceManager* resourceManager);
	void Update(float t_elapsed);
	void Draw(mjCamera* camera, std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix);

private:
    static bool SortByInvDistanceToCamera(mjObject* obj0,mjObject* obj1);



};

}
#endif
