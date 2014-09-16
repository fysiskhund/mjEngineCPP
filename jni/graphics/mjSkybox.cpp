#include "mjSkybox.h"

namespace mjEngine {


mjSkybox::mjSkybox()
{
	scale.Set(10,10,10);
}

void mjSkybox::PushLevel(GLuint texture)
{
	levels.push_back(texture);
}
void mjSkybox::SetModels(mjModel* boxModel, mjModel* planeModel)
{
	this->boxModel = boxModel;
	this->planeModel = planeModel;
}

void mjSkybox::SetCameraPos(mjVector3* cameraPos)
{
	this->cameraPos = cameraPos;

}
void mjSkybox::Update(float t_elapsed)
{
	if (cameraPos)
	{
		pos.CopyFrom(*cameraPos);
	}
}
void mjSkybox::Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix)
{
	// turn off depth buffer
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	model = boxModel;
	mjObject::Draw(shaderList, lookAtMatrix, projectionMatrix);

	model = planeModel;
	for(int i = 0; i < levels.size(); i++)
	{
		mjObject::Draw(shaderList, lookAtMatrix, projectionMatrix);
	}


	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
}
}
