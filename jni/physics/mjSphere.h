/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

#ifndef MJSPHERE_H
#define MJSPHERE_H

#include "mjBoundingStructure.h"
#include "../mjVector3.h"

#include <android/log.h>
#define  LOG_TAG    "mj"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

namespace mjEngine{

class mjSphere: public mjBoundingStructure
{
public:
	mjVector3* c;
	float r;
	mjSphere(mjVector3* c, float r);
	mjSphere(mjSphere& copy);
	mjSphere();
};

}


#endif
