/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 #ifndef MJCAMERA_H
#define MJCAMERA_H

#include "../core/mjObject.h"

namespace mjEngine{

class mjCamera: public mjObject{
public:
	mjCamera();
	void GetLookAtMatrix(float* m);
};

}

#endif
