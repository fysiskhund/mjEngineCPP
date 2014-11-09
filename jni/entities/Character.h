#ifndef CHARACTER_H
#define CHARACTER_H

#include "../extLibs/util/mjMultiPlatform.h"

#include "../core/mjObject.h"
#include "../graphics/mjImageLoader.h"
#include "../extLibs/logger/mjLog.h"
using namespace mjEngine;




class Character: public mjObject
{
public:
	Character();
	int footing = 0;
	int jumping = 0;
	void ProcessPhysicsEffects(float t_elapsed) override;
	void ProcessCollisionEffects() override;
	void Update(float t_elapsed) override;
	void UpdatePosition(float t_elapsed) override;
	mjVector3* gravity;
	mjVector3 intrinsecVel;

	void Check();
};


#endif
