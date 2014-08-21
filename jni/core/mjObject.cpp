#include "mjObject.h"

namespace mjEngine{

mjObject::mjObject()
{
	// Vectors are initialised with 0, so no need to set them here

	up.Set(0,1,0);
	dir.Set(0,0,1);
	scale.Set(1,1,1);

	hasKinematics = true;
	canCollide = true;
}

void mjObject::Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix)
{
	float modelMatrix[16];
	float modelViewMatrix[16];
	float modelViewProjectionMatrix[16];

	Matrix4::GetPositionScaleAndRotationMatrix(pos, dir, up, scale, modelMatrix);

	Matrix4::MultiplyMM(modelViewMatrix, 0,
			modelMatrix, 0,
			lookAtMatrix, 0);

	Matrix4::MultiplyMM(modelViewProjectionMatrix, 0,
						modelViewMatrix, 0,
						projectionMatrix, 0);
	//Matrix4::DebugM("mvpp", modelViewProjectionMatrix);

	model->Draw(shaderList, modelViewMatrix, projectionMatrix, modelViewProjectionMatrix);
}
void mjObject::ProcessPhysicsEffects()
{
	accel.Set0();

	for (int i = 0; i < effectStack.size(); i++)
	{
		//if (effectStack[i]->)
	}
}
void mjObject::Update(float t_elapsed)
{

	vel.ScaleAdd(t_elapsed, accel); // vel = vel + delta_t *a

	pos.ScaleAdd(t_elapsed, vel); // pos = pos + delta_t * v


}
}
