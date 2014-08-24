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
void Matrix4::SetLookAtM(float* m, int offsetIgnored,
		mjVector3& pos,
		mjVector3& dir,
		mjVector3& up)
{
	mjVector3 s;
	mjVector3 u;

	dir.Normalize();
	dir.CrossOut(up, &s); // s = dir x up
	s.Normalize();
	s.CrossOut(dir, &u); // u = s x dir

	m[0] = s.x;
	m[1] = u.x;
	m[2] = -dir.x;
	m[3] = 0;

	m[4] = s.y;
	m[5] = u.y;
	m[6] = -dir.y;
	m[7] = 0;

	m[8] = s.z;
	m[9] = u.z;
	m[10] = -dir.z;
	m[11] = 0;

	m[12] = -s.Dot(pos);
	m[13] = -u.Dot(pos);
	m[14] = dir.Dot(pos);
	m[15] = 1;
}

void Matrix4::glhLookAtf2( float *matrix, float *eyePosition3D,
                  float *center3D, float *upVector3D )
{
   float forward[3], side[3], up[3];
   float matrix2[16], resultMatrix[16];
   mjVector3 forwardV;
   mjVector3 sideV;
   mjVector3 upV;
   mjVector3 upVector3DV;


   //------------------
   forward[0] = center3D[0] - eyePosition3D[0];
   forward[1] = center3D[1] - eyePosition3D[1];
   forward[2] = center3D[2] - eyePosition3D[2];
   //NormalizeVector(forward);
   forwardV.CopyFromArray(forward);
   forwardV.Normalize();
   forwardV.CopyToArray(forward);

   //------------------
   //Side = forward x up
   //ComputeNormalOfPlane(side, forward, upVector3D);
   forwardV.CrossOut(upVector3DV, &sideV);
   sideV.Normalize();
   sideV.CopyToArray(side);
   //NormalizeVector(side);


   //------------------
   //Recompute up as: up = side x forward
   //ComputeNormalOfPlane(up, side, forward);
   sideV.CrossOut(forwardV, &upV);
   upV.CopyToArray(up);

   //------------------
   matrix2[0] = side[0];
   matrix2[4] = side[1];
   matrix2[8] = side[2];
   matrix2[12] = 0.0;
   //------------------
   matrix2[1] = up[0];
   matrix2[5] = up[1];
   matrix2[9] = up[2];
   matrix2[13] = 0.0;
   //------------------
   matrix2[2] = -forward[0];
   matrix2[6] = -forward[1];
   matrix2[10] = -forward[2];
   matrix2[14] = 0.0;
   //------------------
   matrix2[3] = matrix2[7] = matrix2[11] = 0.0;
   matrix2[15] = 1.0;
   //------------------
   Matrix4::MultiplyMM(resultMatrix, 0,
		   	   	   	   matrix, 0,
		   	   	   	   matrix2, 0);
   SetTranslationM(resultMatrix, 0,
                  -eyePosition3D[0], -eyePosition3D[1], -eyePosition3D[2]);
   //------------------
   memcpy(matrix, resultMatrix, 16*sizeof(float));
}

void Matrix4::SetScaleM(float* m, int offsetIgnored, float sX, float sY, float sZ){
	m[0] = sX;
	m[5] = sY;
	m[10] = sZ;
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0;
	m[15] = 1;
}

void Matrix4::SetTranslationM(float* m, int offsetIgnored, float tX, float tY, float tZ){
	m[0] = m[5] = m[10] = m[15] = 1;

	m[12] = tX;
	m[13] = tY;
	m[14] = tZ;

	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] =  0;

}

void Matrix4::DebugM(const char* name, float* m)
{
	for(int i = 0; i< 16; i++)
	{
		LOGI("%s[%d]:%3.3f", name, i, m[i]);
	}
}


}
