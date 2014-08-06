#include "Matrix.h"

namespace mjEngine{

void Matrix4::SetIdentityM(float* m, int ignoredMOffset)
{
	m[0] = m[5] = m[10] = m[15] = 1;
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0;
}


void Matrix4::FrustumM(float* m, int ignoredMOffset,
		float left, float right, float bottom, float top, float near, float far)
{

	float A = (right + left)/(right - left);
	float B = (top + bottom)/(top - bottom);
	float C = -(far + near)/(far - near);
	float D = -2*far*near/(far - near);


	m[0] = 2*near/(right - left);
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;

	m[4] = 0;
	m[5] = 2*near/(top - bottom);
	m[6] = 0;
	m[7] = 0;

	m[8] = A;
	m[9] = B;
	m[10] = C;
	m[11] = -1;

	m[12] = 0;
	m[13] = 0;
	m[14] = D;
	m[15] = 0;
}
void Matrix4::OrthoM(float* m, int ignoredMOffset, float left, float right, float bottom, float top, float near, float far)
{
	float tx = (right + left)/(right - left);
	float ty = (top + bottom)/(top - bottom);
	float tz = (far + near)/(far - near);

	m[0] = 2/(right - left);
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;

	m[4] = 0;
	m[5] = 2/(top - bottom);
	m[6] = 0;
	m[7] = 0;

	m[8] = 0;
	m[9] = 0;
	m[10] = -2.0/(far - near);
	m[11] = 0;

	m[12] = tx;
	m[13] = ty;
	m[14] = tz;
	m[15] = 1;
}

void Matrix4::GetPositionScaleAndRotationMatrix(mjVector3& pos, mjVector3& dir, mjVector3& up, mjVector3& scale, float* matrixR)
{
	mjVector3 s;
	mjVector3 u;

	up.CrossOut(dir, &s);
	dir.CrossOut(s, &u);

	matrixR[0] = s.x*scale.x;
	matrixR[1] = s.y*scale.y;
	matrixR[2] = s.z*scale.z;
	matrixR[3] = 0;

	matrixR[4] = u.x*scale.x;
	matrixR[5] = u.y*scale.y;
	matrixR[6] = u.z*scale.z;
	matrixR[7] = 0;

	matrixR[8] = dir.x*scale.x;
	matrixR[9] = dir.y*scale.y;
	matrixR[10] = dir.z*scale.z;
	matrixR[11] = 0;

	matrixR[12] = pos.x;
	matrixR[13] = pos.y;
	matrixR[14] = pos.z;
	matrixR[15] = 1;
}

}
