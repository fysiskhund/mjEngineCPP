#ifndef MJMODEL_H
#define MJMODEL_H


#include <stdio.h>
#include <string.h>
#include <vector>



//#include <android/log.h>

#include "animation/mjModelPose.h"
#include "mjModelMesh.h"
#include "mjShader.h"
#include "../core/mjConstants.h"

#include <extLibs/math/Matrix.h>
#include <extLibs/math/mjMatrixStack.h>
#include <extLibs/tinyxml/tinyxml2.h>
#include <graphics/animation/mjModelStructure.h>
#include <graphics/renderer/mjRendererData.h>


namespace mjEngine{

using namespace tinyxml2;

#define MJMODEL_MAXATTRSIZE 96


class mjModel
{
public:
    GLfloat* vertexBufferData;
    GLfloat* texCoordBufferData;
    GLfloat* normalComponentBufferData;
	mjModelStructure* structure = NULL;


    float bounds[6] = {  MJ_OVER_9000,  MJ_OVER_9000,  MJ_OVER_9000,
                        -MJ_OVER_9000, -MJ_OVER_9000, -MJ_OVER_9000};

	char status[1024];


    int numVertices;

    mjRendererData* rendererData = NULL;


	std::vector<mjModelMesh*> meshes;

	mjModel();

    virtual void LoadFromMemory(const unsigned char* buffer, size_t totalLength);

    void Load(tinyxml2::XMLDocument* doc);

    mjModelPose* CreateSimplePose();

    void TieStructureToMeshes();
    void TiePoseToStructure();

private:

	int currentVertex;
	int currentFace;
	int faceCount;
    //mjMatrixStack mStack;


};
} // nameSpace mj

#endif
