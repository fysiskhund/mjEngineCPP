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
