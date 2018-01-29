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

        mjObject* dolly = nullptr;
        mjVector3 dollyOffset;
	mjCamera();
        void AttachToObject(mjObject* dolly, mjVector3& dollyOffset);
	void GetLookAtMatrix(GLfloat* m);

	void SetAsCurrentCamera();

	static mjCamera* currentCamera;

        virtual void Update(double t_elapsed);
};

}

#endif
