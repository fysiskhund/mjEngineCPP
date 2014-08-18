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
	this->c.Copy(c);

}
mjSphere::mjSphere(mjSphere& copy)
{
	type = MJ_SPHERE;
	this->r = copy.r;
	this->c.Copy(copy.c);

}
}
