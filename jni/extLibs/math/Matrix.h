#ifndef MATRIX_H
#define MATRIX_H

#include "../../mjVector3.h"

#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "mj"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


namespace mjEngine{

class Matrix4{

public:

	static void SetIdentityM(float* m, int ignoredMOffset);

	static void OrthoM(float* m, int ignoredMOffset, float left, float right, float bottom, float top, float near, float far);
	static void FrustumM(float* m, int ignoredMOffset, float left, float right, float bottom, float top, float near, float far);



	static inline void MultiplyMM(float* result, int ignoredResultOffset,
								  float* lhs, int ignoredLhsOffset,
								  float* rhs, int ignoredRhsOffset){

		result[0] = lhs[0]*rhs[0] + lhs[1]*rhs[4] + lhs[2]*rhs[8] + lhs[3]*rhs[12];
		result[1] = lhs[0]*rhs[1] + lhs[1]*rhs[5] + lhs[2]*rhs[9] + lhs[3]*rhs[13];
		result[2] = lhs[0]*rhs[2] + lhs[1]*rhs[6] + lhs[2]*rhs[10] + lhs[3]*rhs[14];
		result[3] = lhs[0]*rhs[3] + lhs[1]*rhs[7] + lhs[2]*rhs[11] + lhs[3]*rhs[15];

		result[4] = lhs[4]*rhs[0] + lhs[5]*rhs[4] + lhs[6]*rhs[8] + lhs[7]*rhs[12];
		result[5] = lhs[4]*rhs[1] + lhs[5]*rhs[5] + lhs[6]*rhs[9] + lhs[7]*rhs[13];
		result[6] = lhs[4]*rhs[2] + lhs[5]*rhs[6] + lhs[6]*rhs[10] + lhs[7]*rhs[14];
		result[7] = lhs[4]*rhs[3] + lhs[5]*rhs[7] + lhs[6]*rhs[11] + lhs[7]*rhs[15];

		result[8] = lhs[8]*rhs[0] + lhs[9]*rhs[4] + lhs[10]*rhs[8] + lhs[11]*rhs[12];
		result[9] = lhs[8]*rhs[1] + lhs[9]*rhs[5] + lhs[10]*rhs[9] + lhs[11]*rhs[13];
	    result[10] = lhs[8]*rhs[2] + lhs[9]*rhs[6] + lhs[10]*rhs[10] + lhs[11]*rhs[14];
	    result[11] = lhs[8]*rhs[3] + lhs[9]*rhs[7] + lhs[10]*rhs[11] + lhs[11]*rhs[15];

	    result[12] = lhs[12]*rhs[0] + lhs[13]*rhs[4] + lhs[14]*rhs[8] + lhs[15]*rhs[12];
   		result[13] = lhs[12]*rhs[1] + lhs[13]*rhs[5] + lhs[14]*rhs[9] + lhs[15]*rhs[13];
   	    result[14] = lhs[12]*rhs[2] + lhs[13]*rhs[6] + lhs[14]*rhs[10] + lhs[15]*rhs[14];
   	    result[15] = lhs[12]*rhs[3] + lhs[13]*rhs[7] + lhs[14]*rhs[11] + lhs[15]*rhs[15];

	}
	static void GetPositionScaleAndRotationMatrix(mjVector3& pos, mjVector3& dir, mjVector3& up, mjVector3& scale, float* matrixR);
	static void SetLookAtM(float* m, int offsetIgnored,
			mjVector3& pos,
			mjVector3& backDir,
			mjVector3& up);

	static void SetScaleM(float* m, int offsetIgnored, float sX, float sY, float sZ);

	static void SetTranslationM(float* m, int offsetIgnored, float tX, float tY, float tZ);

	static void DebugM(const char* name, float* m);
};

}



#endif
