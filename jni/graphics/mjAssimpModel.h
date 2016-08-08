#ifndef MJASSIMPMODEL_H
#define MJASSIMPMODEL_H

#ifdef USE_ASSIMP

#include "mjShader.h"
#include "../extLibs/math/Matrix.h"
#include "../extLibs/math/mjMatrixStack.h"
#include "../util/mjResourceManager.h"
#include "mjModel.h"


/* assimp include files. These three are usually needed. */
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace mjEngine{

class mjAssimpModel: public mjModel
{
public:
    const aiScene* scene = NULL;


    aiVector3D scene_min, scene_max, scene_center;

    mjAssimpModel(mjResourceManager* resManager);

    void LoadFromFile(const char* fileName) override;
    void TieShaders(std::vector<mjShader*>& shaderList);
    void Draw(std::vector<mjShader*>& shaderList,
              GLfloat* modelMatrix, GLfloat* lookAtMatrix, GLfloat* modelViewMatrix, GLfloat* projectionMatrix, GLfloat* modelViewProjectionMatrix, mjModelPose* pose, mjMatrixStack* matrixStack) override;


    void RecursiveBuild(aiNode *node, mjMatrixStack* matrixStack);
private:
    mjResourceManager* resManager;

    //std::vector<aiMesh*> unrolledMeshes;

    std::vector<GLuint> glTextureForMaterial;

    void RecursiveDraw(std::vector<mjShader*>& shaderList, float* modelMatrix, float* lookAtMatrix, float* modelViewMatrix, float* projectionMatrix, float* modelViewProjectionMatrix, aiNode *node, mjMatrixStack *matrixStack);

};

}

#endif // USE_ASSIMP
#endif // MJASSIMPMODEL_H
