/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 *
 */
#include "mjVector3.h"

namespace mjEngine{
/*
 *
 */

#define MJ_3_2_PI   4.712388
#define MJ_1_2_PI   1.570796
#define MJ_TWICE_PI 6.283185

 mjVector3::mjVector3()
 {
	x = 0;
	y = 0;
	z = 0;
 }

 mjVector3::mjVector3(mjVector3& copy)
 {
	x = copy.x;
	y = copy.y;
	z = copy.z;
 }
 mjVector3::mjVector3(mjVector3& fromPos, mjVector3& toPos)
 {
     x = toPos.x - fromPos.x;
     y = toPos.y - fromPos.y;
     z = toPos.z - fromPos.z;
 }

 mjVector3::mjVector3(GLfloat x, GLfloat y, GLfloat z)
 {
	this->x = x;
	this->y = y;
	this->z = z;
 }

 void mjVector3::Set(GLfloat x, GLfloat y, GLfloat z)
 {
	this->x = x;
	this->y = y;
	this->z = z;
 }


 void mjVector3::Set0()
 {
	this->x = 0;
	this->y = 0;
	this->z = 0;
 }

 void mjVector3::CopyFrom(mjVector3& v)
 {
	x = v.x;
	y = v.y;
	z = v.z;
 }

 void mjVector3::ScaleCopyFrom(GLfloat a, mjVector3& v)
 {
     x = a*v.x;
     y = a*v.y;
     z = a*v.z;
 }

 void mjVector3::CopyFromArray(GLfloat* v)
 {
	 x = v[0];
	 y = v[1];
	 z = v[2];
 }


 void mjVector3::Add(mjVector3& v)
 {
	x += v.x;
	y += v.y;
	z += v.z;
 }

 void mjVector3::ScaleAdd(GLfloat a, mjVector3& v)
 {
	x += a*v.x;
	y += a*v.y;
	z += a*v.z;
 }

 void mjVector3::Subtract(mjVector3& v)
 {
	x -= v.x;
	y -= v.y;
	z -= v.z;
 }

 void mjVector3::ScaleSubtract(GLfloat a, mjVector3& v)
 {
	x -= a*v.x;
	y -= a*v.y;
	z -= a*v.z;
 }

 void mjVector3::MulScalar(GLfloat a)
 {
	x *= a;
	y *= a;
	z *= a;
 }


 GLfloat mjVector3::GetNormSquared()
 {
	return (x*x)+(y*y)+(z*z);
 }

 GLfloat mjVector3::GetNorm()
 {
	return sqrt((x*x)+(y*y)+(z*z));
 }

 GLfloat mjVector3::Normalize()
 {
	GLfloat norm = sqrt((x*x)+(y*y)+(z*z));

	x /= norm;
	y /= norm;
	z /= norm;

	return norm;
 }

 GLfloat mjVector3::Dot(mjVector3& v)
 {
	return (x*v.x) + (y*v.y) + (z*v.z);
 }

 void mjVector3::CrossOut(mjVector3& v, mjVector3* out)
 {
	out->x = (y*v.z) - (z*v.y);
	out->y = (z*v.x) - (x*v.z);
	out->z = (x*v.y) - (y*v.x);
 }

 void mjVector3::CopyToArray(GLfloat* array)
 {
	 array[0] = x;
	 array[1] = y;
	 array[2] = z;
 }

 GLfloat mjVector3::DistanceSquaredTo(mjVector3& v1)
 {
	 mjVector3 v0v1(v1);

	 v0v1.Subtract(*this);
	 return v0v1.GetNorm();
 }
 GLfloat mjVector3::DistanceTo(mjVector3& v1)
 {
	 GLfloat dist = DistanceSquaredTo(v1);
	 return sqrt(dist);
 }

void mjVector3::SetRotations(GLfloat theta, GLfloat phi)
{
	x = sin(theta)*cos(phi);
	y = sin(theta)*sin(phi);
	z = cos(theta);
}

bool mjVector3::Check(const char* file, int line)
{
	if ((fabs(x) > 100)||(fabs(y) > 100)||(fabs(z) > 100))
	{
		LOGI("[%s:%d]Weird value: %3.3f %3.3f %3.3f", file, line, x, y ,z);
		return true;
	}
	return false;
}

}


