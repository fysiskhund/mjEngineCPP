/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

#ifndef MJMATHHELPER_H
#define MJMATHHELPER_H

#include "../../core/mjVector3.h"

#include "../logger/mjLog.h"

namespace mjEngine{

class mjMathHelper{
public:
	static float Sign(float x);
	static void GetForwardAndLeftDirections(mjVector3& cameraDirection, mjVector3& gravity, mjVector3* outForwardDirection, mjVector3* outLeftDirection);
private:
};

}

#endif
