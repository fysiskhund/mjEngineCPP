/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MATRIX_H
#define MATRIX_H

#include "../../mjVector3.h"

#include <jni.h>
#include <android/log.h>
#include <string.h>
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

		result[0] = (lhs[0]*rhs[0]) + (lhs[4]*rhs[1]) + (lhs[8]*rhs[2]) + (lhs[12]*rhs[3]);
		result[1] = (lhs[1]*rhs[0]) + (lhs[5]*rhs[1]) + (lhs[9]*rhs[2]) + (lhs[13]*rhs[3]);
		result[2] = (lhs[2]*rhs[0]) + (lhs[6]*rhs[1]) + (lhs[10]*rhs[2]) + (lhs[14]*rhs[3]);
		result[3] = (lhs[3]*rhs[0]) + (lhs[7]*rhs[1]) + (lhs[11]*rhs[2]) + (lhs[15]*rhs[3]);

		result[4] = (lhs[0]*rhs[4]) + (lhs[4]*rhs[5]) + (lhs[8]*rhs[6]) + (lhs[12]*rhs[7]);
		result[5] = (lhs[1]*rhs[4]) + (lhs[5]*rhs[5]) + (lhs[9]*rhs[6]) + (lhs[13]*rhs[7]);
		result[6] = (lhs[2]*rhs[4]) + (lhs[6]*rhs[5]) + (lhs[10]*rhs[6]) + (lhs[14]*rhs[7]);
		result[7] = (lhs[3]*rhs[4]) + (lhs[7]*rhs[5]) + (lhs[11]*rhs[6]) + (lhs[15]*rhs[7]);

		result[8]  = (lhs[0]*rhs[8]) + (lhs[4]*rhs[9]) + (lhs[8]* rhs[10])  + (lhs[12]*rhs[11]);
		result[9]  = (lhs[1]*rhs[8]) + (lhs[5]*rhs[9]) + (lhs[9]* rhs[10])  + (lhs[13]*rhs[11]);
		result[10] = (lhs[2]*rhs[8]) + (lhs[6]*rhs[9]) + (lhs[10]*rhs[10]) + (lhs[14]*rhs[11]);
		result[11] = (lhs[3]*rhs[8]) + (lhs[7]*rhs[9]) + (lhs[11]*rhs[10]) + (lhs[15]*rhs[11]);

		result[12] = (lhs[0]*rhs[12]) + (lhs[4]*rhs[13]) + (lhs[8]*rhs[14]) + (lhs[12]*rhs[15]);
		result[13] = (lhs[1]*rhs[12]) + (lhs[5]*rhs[13]) + (lhs[9]*rhs[14]) + (lhs[13]*rhs[15]);
		result[14] = (lhs[2]*rhs[12]) + (lhs[6]*rhs[13]) + (lhs[10]*rhs[14]) + (lhs[14]*rhs[15]);
		result[15] = (lhs[3]*rhs[12]) + (lhs[7]*rhs[13]) + (lhs[11]*rhs[14]) + (lhs[15]*rhs[15]);

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
