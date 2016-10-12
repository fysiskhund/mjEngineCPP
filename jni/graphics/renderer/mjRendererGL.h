#ifndef MJRENDERERGL_H
#define MJRENDERERGL_H

#include <graphics/renderer/mjRenderer.h>
#include <graphics/renderer/mjRendererDataGL.h>
#include <graphics/mjModel.h>


namespace mjEngine{

class mjRendererGL: public mjRenderer
{
public:
    //mjRendererGL(mjResourceManager* resourceManager);

    // mjRenderer interface
    void PrepareModel(mjModel &model) override;
    void RenderModel(mjModel &model, float *modelMatrix, float *lookAtMatrix, float *projectionMatrix, mjModelPose *pose, mjMatrixStack *stack,
                     std::vector<mjShader*>* customShaders, int* customTextures, float* extraColorForTexture) override;
    void CleanForModel(mjModel &model) override;

private:
    float modelViewMatrix[16];
    float modelViewProjectionMatrix[16];


};

}

#endif // MJRENDERERGL_H
