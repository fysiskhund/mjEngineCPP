/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 
#ifndef MJCOLLISIONTESTS_H
#define MJCOLLISIONTESTS_H

#include "../mjVector3.h"
#include "mjCollisionResult.h"
#include "mjSphere.h"
#include "mjAABB.h"


#include <android/log.h>
#define  LOG_TAG    "mj"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

namespace mjEngine
{



class mjCollisionTests{
public:

	static mjcolresult SphereVsSphere(mjSphere* s0, mjSphere* s1, mjCollisionResult *out);
	
	static mjcolresult AABBVsAABB(mjAABB& a, mjAABB& b, mjCollisionResult* out);
private:
};


}

#endif
