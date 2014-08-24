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
		switch(effectStack[i]->type)
		{
			case MJ_ACCELERATION:
			case MJ_GRAVITY:
				accel.Add(effectStack[i]->value);

			break;
			default:
				break;
		}

		//if (effectStack[i]->)
	}
	effectStack.clear();

}
void mjObject::Update(float t_elapsed)
{
	if (!boundingStructure.isImmovable)
			{
				vel.Sum(t_elapsed, acc);
				pos.Sum(t_elapsed, vel);

				for (mjPhysicsEffect collisionEffect:collisionStack)
				{
					if (collisionEffect.action != null)
					{s
						switch(collisionEffect.action)
						{
						case changePosition:
							if (collisionEffect.mask[0])
							{
								pos.x = collisionEffect.value.x;
							}
							if (collisionEffect.mask[1])
							{
								pos.y = collisionEffect.value.y;

							}
							if (collisionEffect.mask[2])
							{
								pos.z = collisionEffect.value.z;
							}
							break;

						case addVelocity:
							if (collisionEffect.mask[0])
							{
								vel.x += collisionEffect.value.x;
							}
							if (collisionEffect.mask[1])
							{
								vel.y += collisionEffect.value.y;
							}
							if (collisionEffect.mask[2])
							{
								vel.z += collisionEffect.value.z;
							}
							break;
						}

					}
				}
			}
			collisionStack.clear();

}
}
