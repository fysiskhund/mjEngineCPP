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

#include "../internalMessaging/mjInternalMessageReceiver.h"
//#include "../audio/mjSoundSource.h"





namespace mjEngine{

// Forward declaration
class mjSceneGraph;
class mjMaterialBucket;


class mjObject: public mjInternalMessageReceiver // Generic mjObject for games
{
public:
    char* id = NULL;
    mjSceneGraph* sceneGraph = NULL;
    mjMaterialBucket* rendererBucket = NULL;


    int tag = 0;
	void* tagObject = NULL;

    int   rendererCalculationState = 0; // 0: not calculated yet; 1: the matrix for this object has been calculated
    int   sceneGraphActionState = 0; // 0: Not included, must include. 1: Included, no action needed. 2: Included, must exclude. 3: Excluded, no action
    float rendererMatrix[16];

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
    std::vector<mjModelMesh*>* customMeshes = NULL;


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
    int drawToSubObject = -1; // DO NOT MODIFY THIS VARIABLE DIRECTLY. USE SetDrawToSubObject -1: all subObjects, else draw up to subObject with index N.

    //mjObject(mjResourceManager* resourceManager);
    mjObject(mjResourceManager* resourceManager, structuretype collisionStructureType = MJ_NO_BOUNDING_STRUCT);
	virtual ~mjObject();
    void SetID(const char* id);
    virtual void SetDetailsFromXML(XMLElement* entity);
	virtual void ProcessPhysicsEffects(float t_elapsed);
	virtual void ProcessCollisionEffects();

    //! This should be implemented by the mjObject descendants in your game.
    //! Also remember to "subscribe" this function to a mjInternalMessenger
    virtual void ReceiveInternalMessage(void* contents, unsigned int type, void* sender) override;

    virtual void Update(float t_elapsed);
	virtual void UpdatePosition(float t_elapsed);
    virtual void FlushPhysicsEffects();


    void SetDrawToSubObject(int drawToSubObjectNew);
    void RefreshRendererBucket();

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
