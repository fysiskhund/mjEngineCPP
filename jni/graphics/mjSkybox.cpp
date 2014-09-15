#include "mjSkybox.h"

namespace mjEngine {

void mjSkybox::SetCameraPos(mjVector3* cameraPos)
{
	this->cameraPos = cameraPos;
}
void mjSkybox::Update(float t_elapsed)
{

}
void mjSkybox::Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix)
{
mjObject::Draw(shaderList, lookAtMatrix, projectionMatrix);
}
}
