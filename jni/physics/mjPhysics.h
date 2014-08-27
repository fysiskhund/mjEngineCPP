/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

 
#ifndef MJPHYSICS_H
#define MJPHYSICS_H

#include <vector>
#include "../mjVector3.h"
#include "../core/mjObject.h"
#include "mjCollisionResult.h"
#include "mjCollisionTests.h"

#include <android/log.h>
#define  LOG_TAG    "mj"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

namespace mjEngine
{

class mjPhysics{
public:


	mjPhysics();


	void Update(float delta_t);
	mjVector3 gravity;
	void AddObject(mjObject* object, int collisionLayer);

private:
	std::vector<mjObject*> allObjects;
	std::vector<mjObject*> objectsWithKinematics;
	std::vector<std::vector<mjObject*>* > collisionLayers;

	void CollisionDetection();
	void ProcessPhysicsEffects(float t_elapsed);

};


}

#endif
