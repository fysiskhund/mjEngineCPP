#ifndef MJPHYSICS
#define MJPHYSICS

#include "../mjVector3.h"
#include <vector>

namespace mjEngine
{

class mjPhysics{
public:


	mjPhysics();


	void Update(float delta_t);

private:
std::vector<mjObject> objects;

};


}

#endif
