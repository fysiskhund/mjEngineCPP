#ifndef MJMODEL_H
#define MJMODEL_H


#include <stdio.h>
#include <string.h>
#include <vector>

//#include <android/log.h>

#include "mjModelMesh.h"
#include "../extLibs/tinyxml2.h"


using namespace tinyxml2;

class mjModel
{
public:
	float* vertexBuffer;
	float* texCoordBuffer;
	float* normalComponentBuffer;


	float* bounds;

	char status[1024];

	int glTexture;


	std::vector<mjModelMesh*> meshes;

	mjModel();

	void LoadFromFile(char* fileName);

	void Load(XMLDocument* doc);

private:
	int numVertices;
	int currentVertex;
	int currentFace;
	int faceCount;

};

#endif
