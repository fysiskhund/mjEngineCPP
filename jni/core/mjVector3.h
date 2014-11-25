/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

#ifndef MJVECTOR3_H
#define MJVECTOR3_H

#include <math.h>
#include <stdio.h>
#include "../extLibs/logger/mjLog.h"

namespace mjEngine{

class mjVector3
{
public:
	mjVector3();
	mjVector3(mjVector3& copy);
	mjVector3(float x, float y, float z);

	void Set(float x, float y, float z);
	void Set0();

	void CopyFrom(mjVector3& v);
	void CopyFromArray(float* v);

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

	void CopyToArray(float* array);

	float DistanceSquaredTo(mjVector3& v1);

	float DistanceTo(mjVector3& v1);


	void SetRotations(float theta, float phi);

	bool Check(const char* file, int line);

	float x;
	float y;
	float z;
private:

};







}
#endif
