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
                     std::vector<mjShader*>* customShaders, GLuint* customTextures, std::vector<mjModelMesh*>* customMeshes,
                     float* extraColorForTexture, std::vector<mjShader*>& shaderList) override;
    void CleanForModel(mjModel &model) override;


private:
    float modelViewMatrix[16];
    float modelViewProjectionMatrix[16];

    mjModel* naiveLastModel = NULL;
    int naiveLastTexture = 0;
    mjShader* naiveLastShader = NULL;



};

}

#endif // MJRENDERERGL_H
