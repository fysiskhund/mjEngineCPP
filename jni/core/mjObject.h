#ifndef MJOBJECT
#define MJOBJECT

#include "../mjVector3.h"
#include "../graphics/mjModel.h"
#include "../extLibs/math/Matrix.h"
namespace mjEngine{


class mjObject // Generic mjObject for games
{
public:
	mjVector3 pos;
	mjVector3 dir;
	mjVector3 up;

	mjVector3 scale;

	mjVector3 vel;
	float mass = 1;

	mjModel* model;

	mjObject();
	void Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix);
};
}
#endif
