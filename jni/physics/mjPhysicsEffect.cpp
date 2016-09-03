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
void mjPhysicsEffect::Reset()
{
    type = MJ_NONE;
    action= MJ_ADD_ACCEL;
    value.Set0();
    mask[0] = mask[1] = mask[2] = 1;
    otherObject = NULL;
}

}
