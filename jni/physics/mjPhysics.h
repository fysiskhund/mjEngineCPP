#ifndef MJPHYSICS
#define MJPHYSICS

#include <vector>
#include "../mjVector3.h"
#include "../core/mjObject.h"


namespace mjEngine
{

class mjPhysics{
public:


	mjPhysics();


	void Update(float delta_t);
	mjVector3 gravity;


private:
	std::vector<mjObject> allObjects;
	std::vector<mjObject> objectsWithKinematics;
	std::vector<std::vector<mjObject> > collisionLayers;
	void CollisionDetection();
	void ProcessPhysicsEffects(float t_elapsed);

};


}

#endif
