#ifndef MJMODEL_H
#define MJMODEL_H


#include <stdio.h>
#include <string.h>
#include <vector>
#include <float.h>

#include "../extLibs/util/mjMultiPlatform.h"



//#include <android/log.h>

#include "animation/mjModelPose.h"
#include "mjModelMesh.h"
#include "mjShader.h"

#include "../extLibs/math/Matrix.h"
#include "../extLibs/tinyxml/tinyxml2.h"
#include "animation/mjModelStructure.h"


namespace mjEngine{

using namespace tinyxml2;

#define MJMODEL_MAXATTRSIZE 96
#define OVER_9000 FLT_MAX

class mjModel
{
public:
	float* vertexBuffer;
	float* texCoordBuffer;
	float* normalComponentBuffer;
	mjModelStructure* structure;


	float bounds[6] = {  OVER_9000,  OVER_9000,  OVER_9000,
                        -OVER_9000, -OVER_9000, -OVER_9000};

	char status[1024];


	std::vector<mjModelMesh*> meshes;

	mjModel();

	void LoadFromFile(const char* fileName);

	void Load(XMLDocument* doc);

	void TieShaders(std::vector<mjShader*>& shaderList);

	void Draw(std::vector<mjShader*>& shaderList,
			float* modelMatrix, float* lookAtMatrix, float* modelViewMatrix, float* projectionMatrix, float* modelViewProjectionMatrix, mjModelPose* pose);

    mjModelPose* CreateSimplePose();

private:
	int numVertices;
	int currentVertex;
	int currentFace;
	int faceCount;

};
} // nameSpace mj

#endif
