#ifndef CHARACTER_H
#define CHARACTER_H

#include <GLES2/gl2.h>

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
	virtual void ProcessCollisionEffects() override;
	virtual void Update(float t_elapsed) override;
	mjVector3* gravity;
	mjVector3 intrinsecVel;

	void Check();
};


#endif
