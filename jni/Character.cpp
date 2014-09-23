#include "Character.h"

Character::Character(structuretype type)
: mjObject(type)
{

}
void Character::ProcessCollisionEffects()
{
	bool previousFootingValue = footing;
	footing = 0;

	for (int i=0; i < collisionStack.size(); i++)
	{
		mjPhysicsEffect* collisionEffect = collisionStack[i];

		LOGI("collisionEffect.value: %3.3f %3.3f %3.3f", collisionEffect->value.x,collisionEffect->value.y, collisionEffect->value.z);
		switch(collisionEffect->action)
		{
		case MJ_ADD_VELOCITY:
			if (gravity)
			{
				mjVector3 gravityNormalized;
				gravityNormalized.CopyFrom(*gravity);
				gravityNormalized.Normalize();
				if (up.Dot(gravityNormalized)< -0.8)
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
			vel.ScaleAdd(-t_elapsed*100.0, *gravity);
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
