/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 *
 */
#include "mjVector3.h"

namespace mjEngine{
/* 
 *
 */

#define MJ_3_2_PI 4.712388
#define MJ_1_2_PI 1.570796
 
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
 
 mjVector3::mjVector3(float x, float y, float z)
 {
	this->x = x;
	this->y = y;
	this->z = z;
 }
 
 void mjVector3::Set(float x, float y, float z)
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
 void mjVector3::CopyFromArray(float* v)
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
 
 void mjVector3::ScaleAdd(float a, mjVector3& v)
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
 
 void mjVector3::ScaleSubtract(float a, mjVector3& v)
 {
	x -= a*v.x;
	y -= a*v.y;
	z -= a*v.z;
 }
 
 void mjVector3::MulScalar(float a)
 {
	x *= a;
	y *= a;
	z *= a;
 }
 
 
 float mjVector3::GetNormSquared()
 {
	return (x*x)+(y*y)+(z*z);
 }
 
 float mjVector3::GetNorm()
 {
	return sqrt((x*x)+(y*y)+(z*z));
 }
 
 float mjVector3::Normalize()
 {
	float norm = sqrt((x*x)+(y*y)+(z*z));
	
	x /= norm;
	y /= norm;
	z /= norm;
	
	return norm;
 }
 
 float mjVector3::Dot(mjVector3& v)
 {
	return (x*v.x) + (y*v.y) + (z*v.z);
 }
 
 void mjVector3::CrossOut(mjVector3& v, mjVector3* out)
 {
	out->x = (y*v.z) - (z*v.y);
	out->y = (z*v.x) - (x*v.z);
	out->z = (x*v.y) - (y*v.x);	
 }
 
 void mjVector3::CopyToArray(float* array)
 {
	 array[0] = x;
	 array[1] = y;
	 array[2] = z;
 }

 float mjVector3::DistanceSquaredTo(mjVector3& v1)
 {
	 mjVector3 v0v1(v1);

	 v0v1.Subtract(*this);
	 return v0v1.GetNorm();
 }
 float mjVector3::DistanceTo(mjVector3& v1)
 {
	 float dist = DistanceSquaredTo(v1);
	 return sqrt(dist);
 }

void mjVector3::SetRotations(float theta, float phi)
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


