#include "mjSkybox.h"

namespace mjEngine {


mjSkybox::mjSkybox()
{
	scale.Set(10,10,10);
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
	mjObject::Draw(shaderList, lookAtMatrix, projectionMatrix);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
}
}
