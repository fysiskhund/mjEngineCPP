/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJOBJECT_H
#define MJOBJECT_H

#include <vector>

#include "../mjVector3.h"
#include "../graphics/mjModel.h"
#include "../extLibs/math/Matrix.h"
#include "../physics/mjBoundingStructure.h"
#include "../physics/mjPhysicsEffect.h"
#include "../physics/mjSphere.h"

namespace mjEngine{


class mjObject // Generic mjObject for games
{
public:
	mjVector3 pos;
	mjVector3 dir;
	mjVector3 up;

	mjVector3 scale;


	mjVector3 accel;
	mjVector3 vel;

	float mass = 1;

	mjModel* model;
	mjBoundingStructure* boundingStructure;

	std::vector<mjPhysicsEffect*> effectStack;
	std::vector<mjPhysicsEffect*> collisionStack;

	bool hasKinematics;
	bool canCollide;
	mjObject();
	mjObject(mjBoundingStructure* structure);
	void Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix);
	void ProcessPhysicsEffects();
	void Update(float t_elapsed);


};
}
#endif
