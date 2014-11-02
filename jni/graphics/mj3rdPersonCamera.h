#ifndef MJ3RDPERSONCAMERA_H
#define MJ3RDPERSONCAMERA_H

#include "../extLibs/util/mjMultiplatform.h"

#include "mjCamera.h"



namespace mjEngine{

class mj3rdPersonCamera: public mjCamera{
public:
	void SetTarget(mjVector3* target, mjVector3& offset);
	void Update(float t_elapsed) override;

	float theta = 0;
	float phi   = 0;
	float r     = 4;

private:
	mjVector3* target;
	mjVector3 offset;

};

}


#endif
