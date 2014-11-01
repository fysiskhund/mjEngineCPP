/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

#ifndef MJOBJECT_H
#define MJOBJECT_H

#include <vector>
#include "../extLibs/tinyxml/tinyxml2.h"
#include "../extLibs/util/mjXMLHelper.h"

#include "../core/mjVector3.h"
#include "../graphics/mjModel.h"
#include "../extLibs/math/Matrix.h"
#include "../physics/mjBoundingStructure.h"
#include "../physics/mjPhysicsEffect.h"
#include "../physics/mjSphere.h"
#include "../physics/mjAABB.h"

namespace mjEngine{


class mjObject // Generic mjObject for games
{
public:
    char* id = NULL;

    int tag = 0;
	void* tagObject = NULL;



	mjVector3 pos;
	mjVector3 dir;
	mjVector3 up;

	mjVector3 scale;


	mjVector3 accel;
	mjVector3 vel;

	float mass = 1;

	float distSqToCamera; // Set by SceneGraph on the previous frame, only from comparison
                          // with pos and only if object is semitransparent.

	mjModel* model;
	mjVector3 modelOffset;
	mjBoundingStructure* boundingStructure;

	std::vector<mjPhysicsEffect*> effectStack;
	std::vector<mjPhysicsEffect*> collisionStack;

	bool hasKinematics = true;
	bool canCollide = true;

	bool autoUpdateStructure = true;
	mjObject();
	mjObject(structuretype collisionStructureType);
    void SetID(const char* id);
    virtual void SetDetailsFromXML(XMLElement* entity);
	virtual void Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix);
	virtual void ProcessPhysicsEffects(float t_elapsed);
	virtual void ProcessCollisionEffects();
	virtual void Update(float t_elapsed);
	virtual void UpdatePosition(float t_elapsed);
	virtual void TieShaders(std::vector<mjShader*>& shaderList);

    void MatchScaleToAABB();
    void MatchAABBToModel();



};
}
#endif
