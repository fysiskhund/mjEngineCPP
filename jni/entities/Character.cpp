#include "Character.h"

Character::Character()
: mjObject(MJ_AABB)
{
	model = new mjModel();
	model->LoadFromFile("/sdcard/mjEngineCPP/char0.mesh.xml");
	mjAABB* charBoundStruct = (mjAABB*) boundingStructure;
	mjVector3 minCorner;
	minCorner.Set(-0.3,0,-0.3);
	mjVector3 maxCorner;
	maxCorner.Set(0.3,1.65, 0.3);
	charBoundStruct->SetCorners(minCorner,maxCorner);


	mjImageLoader imgLoader;
	GLuint glTexture = imgLoader.LoadToGLAndFreeMemory("/sdcard/mjEngineCPP/suit_test.png");
	for (int i = 0; i < model->meshes.size(); i++)
	{
		model->meshes[i]->glTexture = glTexture;
	}
}
void Character::ProcessCollisionEffects()
{
	bool previousFootingValue = footing;
	footing = 0;

	for (int i=0; i < collisionStack.size(); i++)
	{
		mjPhysicsEffect* collisionEffect = collisionStack[i];

		/*if (collisionEffect->value.Check(__FILE__, __LINE__))
		{
			LOGI("CEff: 0x%x, otherObj: 0x%x", collisionEffect, collisionEffect->otherObject);
		}*/
		//LOGI("collisionEffect.value: %3.3f %3.3f %3.3f", collisionEffect->value.x,collisionEffect->value.y, collisionEffect->value.z);
		switch(collisionEffect->action)
		{
		case MJ_ADD_VELOCITY:
			if (gravity)
			{
				mjVector3 velocityNormalized;
				velocityNormalized.CopyFrom(collisionEffect->value);
				velocityNormalized.Normalize();

				mjVector3 gravityNormalized;
				gravityNormalized.CopyFrom(*gravity);
				gravityNormalized.Normalize();
				if (gravityNormalized.Dot(velocityNormalized) < -0.4)
				{
					if (!previousFootingValue)
					{
						LOGI("char: footing -> yes");

					}
					footing = 1;
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
		LOGI("char: footing -> *no*");
	}


	mjObject::ProcessCollisionEffects();


}
void Character::Update(float t_elapsed)
{


	if (intrinsecVel.GetNorm() < 10)
	{

		pos.ScaleAdd(t_elapsed, intrinsecVel);
	} else
	{

	}
	if (gravity)
	{
		if (jumping)
		{

			jumping = 0;
			footing = 0;
			if (vel.GetNorm() < gravity->GetNorm()*100.0)
			{
				//LOGI("Vel: %3.3f, %3.3f, %3.3f", vel.x, vel.y, vel.z);
				vel.ScaleAdd(-t_elapsed*25.0, *gravity);
			}
			LOGI("char: footing -> no (jumping)");
		}
	}

	mjObject::Update(t_elapsed);


}
void Character::Check()
{
	if (pos.GetNorm() > 15)
	{
		LOGI("Weird position %3.3f, %3.3f, %3.3f", pos.x, pos.y, pos.z);
	}
}
