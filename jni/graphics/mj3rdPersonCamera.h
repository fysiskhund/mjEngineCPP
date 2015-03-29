#ifndef MJ3RDPERSONCAMERA_H
#define MJ3RDPERSONCAMERA_H

#include "../extLibs/util/mjMultiPlatform.h"

#include "mjCamera.h"



namespace mjEngine{

class mj3rdPersonCamera: public mjCamera{
public:
	void SetTarget(mjVector3* target, mjVector3& offset);
	void Update(GLfloat t_elapsed) override;

	GLfloat theta = 0;
	GLfloat phi   = 0;
	GLfloat r     = 4;

private:
	mjVector3* target;
	mjVector3 offset;

};

}


#endif
