/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

#ifndef MJPHYSICSEFFECT_H
#define MJPHYSICSEFFECT_H


#include "../core/mjVector3.h"

namespace mjEngine{


enum EffectType{
    MJ_NONE,
	MJ_ACCELERATION,
	MJ_GRAVITY,
	MJ_COLLISION,
	MJ_FORCE
};
enum EffectAction{
	MJ_ADD_ACCEL,
	MJ_ADD_VELOCITY,
	MJ_CHANGE_POSITION,
	MJ_SET_VELOCITY,
	MJ_ADD_FORCE
	/*,
	MJ_ADD_ROT_ACCEL,
	MJ_ADD_ROT_VELOCITY*/

};

//Forward declaration to get around the circular reference
class mjObject;
//

class mjPhysicsEffect
{
public:
    EffectType type = MJ_NONE;
	EffectAction action= MJ_ADD_ACCEL;
	mjVector3 value;
	signed char mask[3] = {1, 1, 1};

	mjObject* otherObject;

	mjPhysicsEffect();
	mjPhysicsEffect(EffectType type, EffectAction action);

    void Reset();
private:
};
}
#endif
