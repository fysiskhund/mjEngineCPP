#ifndef MJMESHRENDERER_H
#define MJMESHRENDERER_H

#include <extLibs/util/mjMultiPlatform.h>

#include <graphics/mjModel.h>
#include <graphics/mjModelMesh.h>

#include <graphics/mjShader.h>
#include <graphics/mjDefaultShaders.h>

#include <graphics/renderer/mjRendererData.h>




namespace mjEngine
{

class mjRenderer
{
public:

    int stateSwitchCount = 0;
    virtual void StartCountingStateSwitches();
    virtual void StopCountingStateSwitches();
    virtual void PrepareModel(mjModel& model) = 0;

    virtual void RenderModel(mjModel &model, float *modelMatrix, float *lookAtMatrix, float *projectionMatrix, mjModelPose *pose, mjMatrixStack *stack,
                             std::vector<mjShader*>* customShaders, GLuint* customTextures, std::vector<mjModelMesh*>* customMeshes,
                             float extraColorForTexture[4], std::vector<mjShader*>& shaderList) = 0;

    virtual void CleanForModel(mjModel& model) = 0;

protected:


};

}
#endif // MJRENDERER_H
