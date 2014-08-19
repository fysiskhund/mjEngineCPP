#ifndef MJSPHERE
#define MJSPHERE

#include "mjBoundingStructure.h"
#include "../mjVector3.h"

namespace mjEngine{

class mjSphere: public mjBoundingStructure
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
