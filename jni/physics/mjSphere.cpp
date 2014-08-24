/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */
#include "mjSphere.h"

namespace mjEngine{

mjSphere::mjSphere()
{
	type = MJ_SPHERE;
	r = 0;

}
mjSphere::mjSphere(mjVector3& c, float r)
{
	type = MJ_SPHERE;
	this->r = r;
	this->c.CopyFrom(c);

}
mjSphere::mjSphere(mjSphere& copy)
{
	type = MJ_SPHERE;
	this->r = copy.r;
	this->c.CopyFrom(copy.c);

}
}
