#include "Matrix.h"

namespace mjEngine{

void Matrix4::SetIdentityM(GLfloat* m, int ignoredMOffset)
{
	m[0] = m[5] = m[10] = m[15] = 1;
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0;
}


void Matrix4::FrustumM(GLfloat* m, int ignoredMOffset,
		GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane)
{

	GLfloat A = (right + left)/(right - left);
	GLfloat B = (top + bottom)/(top - bottom);
	GLfloat C = -(farPlane + nearPlane)/(farPlane - nearPlane);
	GLfloat D = -2*farPlane*nearPlane/(farPlane - nearPlane);


	m[0] = 2*nearPlane/(right - left);
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;

	m[4] = 0;
	m[5] = 2*nearPlane/(top - bottom);
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
void Matrix4::OrthoM(GLfloat* m, int ignoredMOffset, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane)
{
	GLfloat tx = (right + left)/(right - left);
	GLfloat ty = (top + bottom)/(top - bottom);
	GLfloat tz = (farPlane + nearPlane)/(farPlane - nearPlane);

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
	m[10] = -2.0/(farPlane - nearPlane);
	m[11] = 0;

	m[12] = tx;
	m[13] = ty;
	m[14] = tz;
	m[15] = 1;
}

void Matrix4::GetPositionScaleAndRotationMatrix(mjVector3& pos, mjVector3& dir, mjVector3& up, mjVector3& scale, GLfloat* matrixR)
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
void Matrix4::GetPositionScaleAndAngleRotationMatrix(mjVector3& pos, mjVector3& angles, GLfloat* matrixR)
{
    GLfloat cosX = cos(angles.x);
    GLfloat cosY = cos(angles.y);
    GLfloat cosZ = cos(angles.z);

    GLfloat sinX = sin(angles.x);
    GLfloat sinY = sin(angles.y);
    GLfloat sinZ = sin(angles.z);


    matrixR[0] = (cosZ*cosY);
	matrixR[1] = ((-sinZ*cosX) + (cosZ*sinY*sinX));
	matrixR[2] = ((sinZ*sinX) + (cosZ*sinY*cosX));
	matrixR[3] = 0;

	matrixR[4] = (sinZ*cosY);
	matrixR[5] = ((cosZ*cosX) + (sinZ*sinY*sinX));
	matrixR[6] = (-(cosZ*sinX) + (sinZ*sinY*cosX));
	matrixR[7] = 0;

	matrixR[8] = -sinY;
	matrixR[9] = (cosY*sinX);
	matrixR[10] = (cosY*cosX);
	matrixR[11] = 0;

	matrixR[12] = pos.x;
	matrixR[13] = pos.y;
	matrixR[14] = pos.z;
    matrixR[15] = 1;
}


void Matrix4::SetLookAtM(GLfloat* m, int offsetIgnored,
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


void Matrix4::SetScaleM(GLfloat* m, int offsetIgnored, GLfloat sX, GLfloat sY, GLfloat sZ){
	m[0] = sX;
	m[5] = sY;
	m[10] = sZ;
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0;
	m[15] = 1;
}

void Matrix4::SetTranslationM(GLfloat* m, int offsetIgnored, GLfloat tX, GLfloat tY, GLfloat tZ){
	m[0] = m[5] = m[10] = m[15] = 1;

	m[12] = tX;
	m[13] = tY;
	m[14] = tZ;

	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] =  0;

}

void Matrix4::SetRotateM(GLfloat* m, int offsetIgnored, GLfloat a, GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat c = cos(a);
	GLfloat s = sin(a);
	GLfloat d = 1.0f-c;



	m[0] = (x*x*(d))+c;
	m[1] = (x*y*(d))+(z*s);
	m[2] = (x*z*(d))-(y*s);
	m[3] = 0;

	m[4] = (x*y*(d))-(z*s);
	m[5] = (y*y*(d))+c;
	m[6] = (y*z*(d))+(x*s);
	m[7] = 0;

	m[8] = (x*z*(d))+(y*s);
	m[9] = (y*z*(d))-(x*s);
	m[10]= (z*z*(d))+c;
	m[11]= 0;

	m[12]= 0;
	m[13]= 0;
	m[14]= 0;
	m[15]= 1;
}

void Matrix4::DebugM(const char* name, GLfloat* m)
{
	for(int i = 0; i< 16; i++)
	{
		LOGI("%s[%d]:%3.3f", name, i, m[i]);
	}
}


}
