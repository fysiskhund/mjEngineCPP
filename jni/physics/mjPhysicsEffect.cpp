#include "mjPhysicsEffect.h"

namespace mjEngine{

mjPhysicsEffect::mjPhysicsEffect()
{
	mask[0] = mask[1] = mask[2] = true;
}

mjPhysicsEffect::mjPhysicsEffect(EffectType type, EffectAction action)
{
	this->type = type;
	this->action = action;

	mask[0] = mask[1] = mask[2] = true;
}

}
