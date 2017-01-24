/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */

#ifndef MJOBJECT_H
#define MJOBJECT_H

#include <vector>
#include <string.h>

#include "../extLibs/util/mjMultiPlatform.h"

#include "../extLibs/tinyxml/tinyxml2.h"
#include "../extLibs/util/mjXMLHelper.h"

#include "../core/mjVector3.h"
#include "../extLibs/math/Matrix.h"
#include "../extLibs/math/mjMatrixStack.h"
#include "../util/mjResourceManager.h"
#include "../graphics/mjModel.h"
#include "../graphics/mjShader.h"
#include "../graphics/animation/mjModelPose.h"
#include "../graphics/animation/mjModelAnimation.h"
#include "../physics/mjBoundingStructure.h"
#include "../physics/mjPhysicsEffect.h"
#include "../physics/mjSphere.h"
#include "../physics/mjAABB.h"
//#include "../audio/mjSoundSource.h"



namespace mjEngine{


class mjObject // Generic mjObject for games
{
public:
    char* id = NULL;

    int tag = 0;
	void* tagObject = NULL;

    unsigned sceneGraphDrawablesIndex = 0;
    unsigned sceneGraphTranslucentsIndex = 0;
    unsigned sceneGraphShadowCastersIndex = 0;

	mjVector3 pos;
	mjVector3 dir;
	mjVector3 up;

	mjVector3 scale;


	mjVector3 accel;
	mjVector3 vel;

	float mass = 1;

	float distSqToCamera; // Set by SceneGraph on the previous frame, only from comparison
                          // with pos and only if object is semitransparent.

    char* modelName = NULL;
    mjModel* model = NULL;
    std::vector<mjShader*>* customShaders = NULL;
    int* customTextures = NULL;
    float extraColorForTexture[4] = {1, 1, 1, 1};

	int animationState = 0;
	mjModelAnimation* animation = NULL;
	mjModelPose* pose = NULL;
	mjVector3 modelOffset;
    mjBoundingStructure* boundingStructure = NULL;

	//mjSoundSource* soundSource;

	std::vector<mjPhysicsEffect*> effectStack;
	std::vector<mjPhysicsEffect*> collisionStack;

	bool hasKinematics = true;
	bool canCollide = true;

	bool autoUpdateStructure = true;

	bool useModelFromXMLDetails = false;
	mjResourceManager* resourceManager;

    std::vector<mjObject*> subObjects;
    int drawToSubObject = -1; // -1: all subObjects, else draw up to subObject N

    //mjObject(mjResourceManager* resourceManager);
    mjObject(mjResourceManager* resourceManager, structuretype collisionStructureType = MJ_NO_BOUNDING_STRUCT);
	virtual ~mjObject();
    void SetID(const char* id);
    virtual void SetDetailsFromXML(XMLElement* entity);
	virtual void ProcessPhysicsEffects(float t_elapsed);
	virtual void ProcessCollisionEffects();
	virtual void Update(float t_elapsed);
	virtual void UpdatePosition(float t_elapsed);
    virtual void FlushPhysicsEffects();


    void CopyModelMatrixTo(float* modelMatrixOut);

    void MatchScaleToAABB();
    void MatchAABBToModel();


    // Debugging functions. These get called by mjPhysics exclusively,
    // and _only_ if DEBUGCOLLISIONS is defined

    virtual void DEBUGonCollisionTestStart(mjObject* otherObject){}
    virtual void OnOverlap(mjObject* otherObject){}


};
}
#endif
