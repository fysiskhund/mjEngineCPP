#ifndef CHARACTER_H
#define CHARACTER_H

#include "core/mjObject.h"
#include "extLibs/logger/mjLog.h"
using namespace mjEngine;


class Character: public mjObject
{
public:
	Character(structuretype type);
	int footing = 0;
	virtual void ProcessCollisionEffects() override;
	mjVector3* gravity;

};


#endif
