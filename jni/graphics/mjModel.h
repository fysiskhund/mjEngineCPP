#ifndef MJMODEL_H
#define MJMODEL_H


#include <stdio.h>
#include <string.h>
#include <vector>
#include <float.h>


//#include <android/log.h>

#include "animation/mjModelPose.h"
#include "mjModelMesh.h"
#include "mjShader.h"

#include <extLibs/math/Matrix.h>
#include <extLibs/math/mjMatrixStack.h>
#include <extLibs/tinyxml/tinyxml2.h>
#include <graphics/animation/mjModelStructure.h>
#include <graphics/renderer/mjRendererData.h>


namespace mjEngine{

using namespace tinyxml2;

#define MJMODEL_MAXATTRSIZE 96
#define OVER_9000 FLT_MAX

class mjModel
{
public:
    GLfloat* vertexBufferData;
    GLfloat* texCoordBufferData;
    GLfloat* normalComponentBufferData;
	mjModelStructure* structure = NULL;


	float bounds[6] = {  OVER_9000,  OVER_9000,  OVER_9000,
                        -OVER_9000, -OVER_9000, -OVER_9000};

	char status[1024];


    int numVertices;

    mjRendererData* rendererData = NULL;


	std::vector<mjModelMesh*> meshes;

	mjModel();

    virtual void LoadFromFile(const char* fileName);

    void Load(tinyxml2::XMLDocument* doc);

    virtual void TieShaders(std::vector<mjShader*>& shaderList);

    virtual void DrawDEPRECATED(std::vector<mjShader*>& shaderList,
            GLfloat* modelMatrix, GLfloat* lookAtMatrix, GLfloat* modelViewMatrix, GLfloat* projectionMatrix, GLfloat* modelViewProjectionMatrix, mjModelPose* pose, mjMatrixStack* matrixStack);

    mjModelPose* CreateSimplePose();

    void TieStructureToMeshes();
    void TiePoseToStructure();

private:

	int currentVertex;
	int currentFace;
	int faceCount;
	mjMatrixStack mStack;


};
} // nameSpace mj

#endif
