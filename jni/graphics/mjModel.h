#ifndef MJMODEL_H
#define MJMODEL_H


#include <stdio.h>
#include <string.h>
#include <vector>

#include "../extLibs/util/mjMultiPlatform.h"



//#include <android/log.h>

#include "animation/mjModelPose.h"
#include "mjModelMesh.h"
#include "mjShader.h"

#include "../extLibs/math/Matrix.h"
#include "../extLibs/tinyxml/tinyxml2.h"


namespace mjEngine{

using namespace tinyxml2;

#define MJMODEL_MAXATTRSIZE 96

class mjModel
{
public:
	float* vertexBuffer;
	float* texCoordBuffer;
	float* normalComponentBuffer;


	float* bounds;

	char status[1024];


	std::vector<mjModelMesh*> meshes;

	mjModel();

	void LoadFromFile(const char* fileName);

	void Load(XMLDocument* doc);

	void TieShaders(std::vector<mjShader*>& shaderList);

	void Draw(std::vector<mjShader*>& shaderList,
			float* modelMatrix, float* modelViewMatrix, float* projectionMatrix, float* modelViewProjectionMatrix, mjModelPose* pose);

private:
	int numVertices;
	int currentVertex;
	int currentFace;
	int faceCount;

};
} // nameSpace mj

#endif
