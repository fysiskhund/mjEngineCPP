/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */


#ifndef MJPHYSICS_H
#define MJPHYSICS_H

#include <vector>
#include "../core/mjVector3.h"
#include "../core/mjObject.h"
#include "mjCollisionResult.h"
#include "mjCollisionTests.h"

#include "../extLibs/logger/mjLog.h"

namespace mjEngine
{

class mjPhysics{
public:

    mjVector3 gravity;
    std::vector<mjPhysicsEffect* > globalEffects;


	bool debugVar = 0;

	mjPhysics();
    virtual ~mjPhysics();


	void Update(float delta_t);

	void AddObject(mjObject* object, int collisionLayer);

	//void AddPhysicsEffect(mjPhysicsEffect* physicsEffect);

    void RemoveAllObjects();

    void CleanUpPools();


private:
	std::vector<mjObject*> allObjects;
	std::vector<mjObject*> objectsWithKinematics;
	std::vector<std::vector<mjObject*>* > collisionLayers;


    int currentColResultAvailableIndex = 0;
    int lastColResultPoolSize = 0;
    std::vector<mjCollisionResult*> colResultPool;


	void CollisionDetection();

	void ProcessPhysicsEffectsAndUpdate(float t_elapsed);
	void ProcessCollisionEffects();
	void UpdatePositions(float t_elapsed);
    void RecycleCollisionResults();
    void FlushObjectsPhysicsEffects();

};


}

#endif
