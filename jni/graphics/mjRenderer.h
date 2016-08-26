#ifndef MJMESHRENDERER_H
#define MJMESHRENDERER_H

#include <extLibs/util/mjMultiPlatform.h>

#include <graphics/mjModel.h>
#include <graphics/mjModelMesh.h>

#include <graphics/mjShader.h>
#include <graphics/mjDefaultShaders.h>


namespace mjEngine
{

class mjRenderer
{
public:
    mjRenderer();
    void PrepareForModel(mjModel& model);

    void RenderModel(mjModel& model, float* modelMatrix, float* lookAtMatrix, float* projectionMatrix, mjModelPose* pose, mjMatrixStack* stack);

    void CleanForModel(mjModel& model);

private:
    void RenderMesh(mjModelMesh& mesh);

    GLuint vertexArrayID[1];
    mjShader* shader;

    GLuint vertexCoordinatesBufferID;
    GLuint uvComponentsBufferID;
    GLuint normalCoordinatesID;

    GLuint* elementBuffersIDs;

};

}
#endif // MJRENDERER_H
