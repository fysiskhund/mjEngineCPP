/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */
#include "mjSphere.h"

namespace mjEngine{

mjSphere::mjSphere()
{
#ifndef NODEBUGDELETEMSG
    LOGI("mjSphere() %x", this);
#endif
	type = MJ_SPHERE;
	r = 0;
	c = new mjVector3();
    LOGI("%s %d: new %s", __FILE__, __LINE__, "vector3");
}


mjSphere::mjSphere(mjVector3* c, float r)
{
#ifndef NODEBUGDELETEMSG
    LOGI("mjSphere() %x", this);
#endif
	type = MJ_SPHERE;

	this->c = c;
	this->r = r;

	//LOGI("sph: c = %p", c);


}
mjSphere::mjSphere(mjSphere& copy)
{
#ifndef NODEBUGDELETEMSG
    LOGI("mjSphere() %x", this);
#endif
	type = MJ_SPHERE;
	this->r = copy.r;
	this->c->CopyFrom(*copy.c);

}

mjSphere::~mjSphere()
{
#ifndef NODEBUGDELETEMSG
    LOGI("~mjSphere() %x", this);
#endif
}
}
