#include "mjPhysicsEffect.h"

namespace mjEngine{

mjPhysicsEffect::mjPhysicsEffect()
{

}

mjPhysicsEffect::mjPhysicsEffect(EffectType type, EffectAction action)
{
	this->type = type;
	this->action = action;

}

}
