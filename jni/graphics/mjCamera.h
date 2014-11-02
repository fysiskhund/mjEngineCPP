/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJCAMERA_H
#define MJCAMERA_H

#include "../extLibs/util/mjMultiPlatform.h"

#include "../core/mjObject.h"

namespace mjEngine{

class mjCamera: public mjObject{
public:
	bool hasKinematics = false;
	mjCamera();
	void GetLookAtMatrix(float* m);
};

}

#endif
