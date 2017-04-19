/*
 * Copyright (C) 2014-17 Alejandro Valenzuela Roca, under LGPLv3 terms.
 */

#ifndef MJVECTOR3_H
#define MJVECTOR3_H

#include <math.h>
#include <stdio.h>
#include "../extLibs/logger/mjLog.h"
#include "../extLibs/util/mjMultiPlatform.h"

namespace mjEngine{

#ifndef MJ_TWICE_PI

// Some useful constants
#define MJ_3_2_PI   4.712388
#define MJ_1_2_PI   1.570796
#define MJ_TWICE_PI 6.283185

#endif

class mjVector3
{
public:
	mjVector3();
	mjVector3(mjVector3& copy);
    mjVector3(mjVector3& fromPos, mjVector3& toPos);
	mjVector3(GLfloat x, GLfloat y, GLfloat z);

	void Set(GLfloat x, GLfloat y, GLfloat z);
	void Set0();
    void SetAll(GLfloat value);

    void ScaleCopyFrom(GLfloat a, mjVector3& v);
	void CopyFrom(mjVector3& v);
	void CopyFromArray(GLfloat* v);

	void Add(mjVector3& v);
	void ScaleAdd(GLfloat a, mjVector3& v);
	void Subtract(mjVector3& v);
	void ScaleSubtract(GLfloat a, mjVector3& v);



	void MulScalar(GLfloat a);

	GLfloat GetNorm();
	GLfloat GetNormSquared();
	GLfloat Normalize();

	GLfloat Dot(mjVector3& v);
	void CrossOut(mjVector3& v, mjVector3* r);

	void CopyToArray(GLfloat* array);

	GLfloat DistanceSquaredTo(mjVector3& v1);
    GLfloat DistanceSquaredTo(float x, float y, float z);

	GLfloat DistanceTo(mjVector3& v1);


	void SetRotations(GLfloat theta, GLfloat phi);

	bool Check(const char* file, int line);

	GLfloat x;
	GLfloat y;
	GLfloat z;
private:

};







}
#endif
