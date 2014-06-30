#ifndef MJMODEL_H
#define MJMODEL_H

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

	int glTexture;


	mjModelMesh* meshes;

	mjModel();

	void Load(char* modelDefinition);

private:
	int numVertices;
	int currentVertex;
	int currentFace;

};

#endif
