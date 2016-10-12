#ifndef MJMESHRENDERER_H
#define MJMESHRENDERER_H

#include <extLibs/util/mjMultiPlatform.h>

#include <graphics/mjModel.h>
#include <graphics/mjModelMesh.h>

#include <graphics/mjShader.h>
#include <graphics/mjDefaultShaders.h>

#include <graphics/renderer/mjRendererData.h>

#include <util/mjResourceManager.h>



namespace mjEngine
{

class mjRenderer
{
public:

    void Initialize(mjResourceManager* resourceManager);

    virtual void PrepareModel(mjModel& model) = 0;

    virtual void RenderModel(mjModel& model, float* modelMatrix, float* lookAtMatrix, float* projectionMatrix, mjModelPose* pose, mjMatrixStack* stack,
                             std::vector<mjShader*>* customShaders, int* customTextures, float* extraColorForTexture) = 0;

    virtual void CleanForModel(mjModel& model) = 0;

protected:
    mjResourceManager* resourceManager = NULL;

};

}
#endif // MJRENDERER_H
