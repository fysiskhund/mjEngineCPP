#ifndef MJPHYSICSEFFECT_H
#define MJPHYSICSEFFECT_H

#include "../core/mjObject.h"
#include "../mjVector3.h"

namespace mjEngine{


enum EffectType{
	MJ_ACCELERATION,
	MJ_GRAVIY,
	MJ_COLLISION
};
enum EffectAction{
	MJ_ADDACCEL,
	MJ_ADDVELOCITY,
	MJ_CHANGEPOSITION,
	MJ_ADDROTACCEL,
	MJ_ADDROTVELOCITY

};

class mjPhysicsEffect
{
public:
	EffectType type = MJ_ACCELERATION;
	EffectAction action= MJ_ADDACCEL;
	mjVector3 value;
	bool mask[3];

	mjObject otherObject;

	mjPhysicsEffect();


private:
};
}
#endif
