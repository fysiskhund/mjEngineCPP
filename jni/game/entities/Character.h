#ifndef CHARACTER_H
#define CHARACTER_H

#include <extLibs/util/mjMultiPlatform.h>

#include <core/mjObject.h>
#include <util/mjResourceManager.h>
#include <graphics/mjImageLoader.h>
#include <extLibs/logger/mjLog.h>
#include <graphics/animation/mjAnimation.h>
#include <graphics/animation/mjAnimationKeyframe.h>
#include <graphics/animation/mjAnimator.h>
#include <graphics/animation/mjModelAnimation.h>
#include <graphics/animation/mjModelPose.h>
using namespace mjEngine;


#define MAX_VEL_FOR_CHARACTER 2

class Character: public mjObject
{
public:

    mjVector3 startPosition;
	Character(mjResourceManager* resourceManager);
	int hasFooting = 0;
	int jumping = -1;

	void ProcessPhysicsEffects(float t_elapsed) override;
	void ProcessCollisionEffects() override;
	void Update(float t_elapsed) override;
	void UpdatePosition(float t_elapsed) override;
	void SetDetailsFromXML(XMLElement* entity) override;
	mjVector3* gravity;
	mjVector3 intrinsecVel;

	mjObject* objectProvidingFooting;

	void Check();
private:
	void SetUpSillyAnimation();
    mjAnimation animation;
    mjAnimator animator;
    float tAnimation = 0;

};


#endif
