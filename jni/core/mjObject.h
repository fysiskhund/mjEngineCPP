#ifndef MJOBJECT_H
#define MJOBJECT_H

#include <vector>

#include "../mjVector3.h"
#include "../graphics/mjModel.h"
#include "../extLibs/math/Matrix.h"
#include "../physics/mjPhysicsEffect.h"

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

	std::vector<mjPhysicsEffect*> effectStack;
	std::vector<mjPhysicsEffect*> collisionStack;

	bool hasKinematics;
	bool canCollide;
	mjObject();
	void Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix);
	void ProcessPhysicsEffects();
	void Update(float t_elapsed);
};
}
#endif
