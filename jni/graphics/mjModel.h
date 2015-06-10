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
#include "../extLibs/math/mjMatrixStack.h"
#include "../extLibs/tinyxml/tinyxml2.h"
#include "animation/mjModelStructure.h"


namespace mjEngine{

using namespace tinyxml2;

#define MJMODEL_MAXATTRSIZE 96
#define OVER_9000 FLT_MAX

class mjModel
{
public:
	GLfloat* vertexBuffer;
	GLfloat* texCoordBuffer;
	GLfloat* normalComponentBuffer;
	mjModelStructure* structure = NULL;


	float bounds[6] = {  OVER_9000,  OVER_9000,  OVER_9000,
                        -OVER_9000, -OVER_9000, -OVER_9000};

	char status[1024];


	std::vector<mjModelMesh*> meshes;

	mjModel();

	void LoadFromFile(const char* fileName);

	void Load(XMLDocument* doc);

	void TieShaders(std::vector<mjShader*>& shaderList);

	void Draw(std::vector<mjShader*>& shaderList,
			GLfloat* modelMatrix, GLfloat* lookAtMatrix, GLfloat* modelViewMatrix, GLfloat* projectionMatrix, GLfloat* modelViewProjectionMatrix, mjModelPose* pose);

    mjModelPose* CreateSimplePose();

    void TieStructureToMeshes();
    void TiePoseToStructure();

private:
	int numVertices;
	int currentVertex;
	int currentFace;
	int faceCount;
	mjMatrixStack mStack;




#ifdef OSX
    GLuint vertexArrayObject;
    GLuint objectBuffers[3];
#endif

};
} // nameSpace mj

#endif
