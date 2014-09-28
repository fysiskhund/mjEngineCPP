#include "mjObject.h"

namespace mjEngine{

mjObject::mjObject(structuretype collisionStructureType)
{
	// Vectors are initialised with 0, so no need to set them here

	up.Set(0,1,0);
	dir.Set(0,0,1);
	scale.Set(1,1,1);

	switch(collisionStructureType)
	{
	case MJ_AABB:
	{
		mjVector3 maxCorner;
		maxCorner.Set(0.5,1.0,0.5);

		mjVector3 minCorner;
		minCorner.Set(-0.5,0,-0.5);

		mjAABB* aabb = new mjAABB(&pos, minCorner, maxCorner, false);
		this->boundingStructure = aabb;
		aabb->center = &pos;
		LOGI("Object initialised as AABB");
	}
		break;
	default:
		break;
	}

}
mjObject::mjObject()
{
	// Vectors are initialised with 0, so no need to set them here

	up.Set(0,1,0);
	dir.Set(0,0,1);
	scale.Set(1,1,1);


	boundingStructure = new mjSphere(&pos, 1);
}

void mjObject::TieShaders(std::vector<mjShader*>& shaderList)
{
	model->TieShaders(shaderList);
}

void mjObject::Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix)
{
	float modelMatrix[16];
	float modelViewMatrix[16];
	float modelViewProjectionMatrix[16];
	mjVector3 positionPlusOffset;
	positionPlusOffset.CopyFrom(pos);
	positionPlusOffset.Add(modelOffset);

	Matrix4::GetPositionScaleAndRotationMatrix(positionPlusOffset, dir, up, scale, modelMatrix);

	Matrix4::MultiplyMM(modelViewMatrix, 0,
			lookAtMatrix, 0,
			modelMatrix, 0);

	Matrix4::MultiplyMM(modelViewProjectionMatrix, 0,
						projectionMatrix, 0,
						modelViewMatrix, 0);
	//Matrix4::DebugM("mvpp", modelViewProjectionMatrix);

	model->Draw(shaderList, modelMatrix, modelViewMatrix, projectionMatrix, modelViewProjectionMatrix);
}

void mjObject::ProcessPhysicsEffects(float t_elapsed)
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

	if (!boundingStructure->isImmovable)
	{

		vel.ScaleAdd(t_elapsed, accel);

	}
}
void mjObject::ProcessCollisionEffects()
{
	if (!boundingStructure->isImmovable)
	{
		for (int i=0; i < collisionStack.size(); i++)//(mjPhysicsEffect collisionEffect:collisionStack)
		{
			mjPhysicsEffect* collisionEffect = collisionStack[i];
			switch(collisionEffect->action)
			{
			case MJ_CHANGE_POSITION:
				//LOGI("change position");
				if (collisionEffect->mask[0])
				{
					pos.x = collisionEffect->value.x;
				}
				if (collisionEffect->mask[1])
				{
					pos.y = collisionEffect->value.y;

				}
				if (collisionEffect->mask[2])
				{
					pos.z = collisionEffect->value.z;
				}
				break;

			case MJ_ADD_VELOCITY:
				if (collisionEffect->mask[0])
				{
					vel.x += collisionEffect->value.x;
				}
				if (collisionEffect->mask[1])
				{
					//LOGI("Add velocity: %3.3f + %3.3f", vel.y, collisionEffect->value.y);
					vel.y += collisionEffect->value.y;
				}
				if (collisionEffect->mask[2])
				{
					vel.z += collisionEffect->value.z;
				}
				break;
			case MJ_SET_VELOCITY:
				if (collisionEffect->mask[0])
				{
					vel.x = collisionEffect->value.x;
				}
				if (collisionEffect->mask[1])
				{
					vel.y = collisionEffect->value.y;
				}
				if (collisionEffect->mask[2])
				{
					vel.z = collisionEffect->value.z;
				}
				break;
			case MJ_ADD_ACCEL:
				if (collisionEffect->mask[0])
				{
					accel.x += collisionEffect->value.x;
				}
				if (collisionEffect->mask[1])
				{
					accel.y += collisionEffect->value.y;
				}
				if (collisionEffect->mask[2])
				{
					accel.z += collisionEffect->value.z;
				}
				break;
			}

		}
	}
	collisionStack.clear();
}
void mjObject::Update(float t_elapsed)
{

}
void mjObject::UpdatePosition(float t_elapsed)
{
	pos.ScaleAdd(t_elapsed, vel);

	// Update underlying mjBoundingStructure data if necessary
	if (autoUpdateStructure)
	{
		switch(boundingStructure->type)
		{
		case MJ_AABB:
		{
			mjAABB* aabb = (mjAABB*) boundingStructure;
			aabb->UpdateCorners();
		}
		break;
		default:
			break;
		}
	}
}
}
