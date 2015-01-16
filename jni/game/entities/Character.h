#ifndef CHARACTER_H
#define CHARACTER_H

#include <extLibs/util/mjMultiPlatform.h>

#include <core/mjObject.h>
#include <util/mjResourceManager.h>
#include <graphics/mjImageLoader.h>
#include <extLibs/logger/mjLog.h>
using namespace mjEngine;


#define MAX_VEL_FOR_CHARACTER 2

class Character: public mjObject
{
public:

    mjVector3 startPosition;
	Character(mjResourceManager& resourceManager);
	int footing = 0;
	int jumping = 0;
	void ProcessPhysicsEffects(float t_elapsed) override;
	void ProcessCollisionEffects() override;
	void Update(float t_elapsed) override;
	void UpdatePosition(float t_elapsed) override;
	void SetDetailsFromXML(XMLElement* entity) override;
	mjVector3* gravity;
	mjVector3 intrinsecVel;

	mjObject* objectProvidingFooting;

	void Check();
};


#endif
