#ifndef MJVECTOR3
#define MJVECTOR3

#include <math.h>

namespace mjEngine{

class mjVector3
{
public:
	mjVector3();
	mjVector3(mjVector3& copy);
	mjVector3(float x, float y, float z);
	
	void Set(float x, float y, float z);
	
	void Copy(mjVector3& v);
	
	void Add(mjVector3& v);
	void ScaleAdd(float a, mjVector3& v);
	void Subtract(mjVector3& v);
	void ScaleSubtract(float a, mjVector3& v);
	
	void MulScalar(float a);
	
	float GetNorm();
	float GetNormSquared();
	float Normalize();
	
	float Dot(mjVector3& v);
	void CrossOut(mjVector3& v, mjVector3* r);
	
	
	float x;
	float y;
	float z;
private:

};







}
#endif