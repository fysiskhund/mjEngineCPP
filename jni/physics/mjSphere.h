#ifndef MJSPHERE
#define MJSPHERE

#include "mjCollisionStructure.h"
#include "../mjVector3.h"

namespace mjEngine{

class mjSphere: public mjCollisionStructure
{
public:
	mjVector3 c;
	float r;
	mjSphere(mjVector3& c, float r);
	mjSphere(mjSphere& copy);
	mjSphere();
};

}


#endif
