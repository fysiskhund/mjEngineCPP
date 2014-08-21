#ifndef MJPHYSICSEFFECT_H
#define MJPHYSICSEFFECT_H


#include "../mjVector3.h"

namespace mjEngine{


enum EffectType{
	MJ_ACCELERATION,
	MJ_GRAVIY,
	MJ_COLLISION
};
enum EffectAction{
	MJ_ADD_ACCEL,
	MJ_ADD_VELOCITY,
	MJ_CHANGE_POSITION,
	MJ_ADD_ROT_ACCEL,
	MJ_ADD_ROT_VELOCITY

};

//Forward declaration to get around the circular reference
class mjObject;
//

class mjPhysicsEffect
{
public:
	EffectType type = MJ_ACCELERATION;
	EffectAction action= MJ_ADD_ACCEL;
	mjVector3 value;
	bool mask[3];

	mjObject* otherObject;

	mjPhysicsEffect();


private:
};
}
#endif
