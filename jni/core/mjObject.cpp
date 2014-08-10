#include "mjObject.h"

namespace mjEngine{

mjObject::mjObject()
{
	pos.Set(0,0,0);
	up.Set(0,1,0);
	dir.Set(0,0,1);
	scale.Set(1,1,1);
}

void mjObject::Draw(std::vector<mjShader*>& shaderList, float* projectionMatrix)
{
	float modelViewMatrix[16];
	float modelViewProjectionMatrix[16];

	Matrix4::GetPositionScaleAndRotationMatrix(pos, dir, up, scale, modelViewMatrix);

	Matrix4::MultiplyMM(modelViewProjectionMatrix, 0,
						modelViewMatrix, 0,
						projectionMatrix, 0);

	model->Draw(shaderList, projectionMatrix, modelViewMatrix, modelViewProjectionMatrix);
}
}
