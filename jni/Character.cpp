#include "Character.h"

Character::Character(structuretype type)
: mjObject(type)
{

}
void Character::ProcessCollisionEffects()
{
	for (int i=0; i < collisionStack.size(); i++)//(mjPhysicsEffect collisionEffect:collisionStack)
	{
		mjPhysicsEffect* collisionEffect = collisionStack[i];
		switch(collisionEffect->action)
		{
		case MJ_ADD_VELOCITY:
			if (gravity)
			{
				mjVector3 gravityNormalized;
				gravityNormalized.CopyFrom(*gravity);
				gravityNormalized.Normalize();
				if (up.Dot(gravityNormalized)< - 0.3)
				{
					if (!footing)
					{
						LOGI("char: footing -> yes");
						footing = 1;
					}
				}
			}
			break;
		default:
			//whatever
			break;
		}
	}
	mjObject::ProcessCollisionEffects();

}
