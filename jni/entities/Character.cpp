#include "Character.h"

Character::Character(mjResourceManager& resourceManager)
: mjObject(MJ_AABB)
{
	model = resourceManager.FetchModel("char0.mesh.xml");
	mjAABB* charBoundStruct = (mjAABB*) boundingStructure;
	mjVector3 minCorner;
	minCorner.Set(-0.3,0,-0.3);
	mjVector3 maxCorner;
	maxCorner.Set(0.3,1.65, 0.3);
	charBoundStruct->SetCorners(minCorner,maxCorner);



	GLuint glTexture = resourceManager.FetchTexture("suit_test.png");
	for (unsigned i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}
}
void Character::ProcessPhysicsEffects(float t_elapsed)
{
	accel.Set0();

	for (unsigned i = 0; i < effectStack.size(); i++)
	{
		switch(effectStack[i]->type)
		{
			case MJ_ACCELERATION:
			case MJ_GRAVITY:
				accel.Add(effectStack[i]->value);

			break;
			case MJ_FORCE:
                if (effectStack[i]->value.GetNorm() > 3)
                {
                    accel.ScaleAdd(1.0/mass, effectStack[i]->value);
                }
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
void Character::ProcessCollisionEffects()
{
	int previousFootingValue = footing;
	int characterHasFootingThisFrame = 0;

	for (unsigned i=0; i < collisionStack.size(); i++)
	{
		mjPhysicsEffect* collisionEffect = collisionStack[i];

		/*if (collisionEffect->value.Check(__FILE__, __LINE__))
		{
			LOGI("CEff: 0x%x, otherObj: 0x%x", collisionEffect, collisionEffect->otherObject);
		}*/
		//LOGI("collisionEffect.value: %3.3f %3.3f %3.3f", collisionEffect->value.x,collisionEffect->value.y, collisionEffect->value.z);
		switch(collisionEffect->action)
		{
		case MJ_CHANGE_POSITION:
			if (gravity) // If gravity is set..
			{
				mjVector3 repositionNormalized;

				repositionNormalized.CopyFrom(collisionEffect->value);
				repositionNormalized.Subtract(pos);
				repositionNormalized.Normalize();

				mjVector3 gravityNormalized;
				gravityNormalized.CopyFrom(*gravity);
				gravityNormalized.Normalize();
				if (gravityNormalized.Dot(repositionNormalized) < -0.4)
				{
					if (!previousFootingValue)
					{
						LOGI("char: footing -> yes");

					}
					characterHasFootingThisFrame = 1;
				}
			}
			break;
		default:
			//whatever
			break;
		}
	}
	if (previousFootingValue && footing == 0)
	{
	    previousFootingValue
		LOGI("char: footing -> *no*");
	}


	mjObject::ProcessCollisionEffects();


}
void Character::Update(float t_elapsed)
{



	if (gravity)
	{
		if (jumping)
		{

			jumping = 0;
			footing = 0;
			if (vel.GetNorm() < gravity->GetNorm()*100.0)
			{
				//LOGI("Vel: %3.3f, %3.3f, %3.3f", vel.x, vel.y, vel.z);
				vel.ScaleAdd(-t_elapsed*35.0, *gravity);
			}
			LOGI("char: footing -> no (jumping)");
		}
	}

	mjObject::Update(t_elapsed);


}
void Character::UpdatePosition(float t_elapsed)
{
    if (intrinsecVel.GetNorm() < 10)
        {

            pos.ScaleAdd(t_elapsed, intrinsecVel);
        }
	mjObject::UpdatePosition(t_elapsed);
}

void Character::Check()
{
	if (pos.GetNorm() > 15)
	{
		LOGI("Weird position %3.3f, %3.3f, %3.3f", pos.x, pos.y, pos.z);
	}
}

