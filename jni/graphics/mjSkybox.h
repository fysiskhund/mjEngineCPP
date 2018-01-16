#ifndef MJ_SKYBOX_H
#define MJ_SKYBOX_H

#include <vector>
#include "../extLibs/util/mjMultiPlatform.h"


#include "../core/mjObject.h"
#include "../util/mjResourceManager.h"

#include "mjImageLoader.h"
#include "mjSkyboxLevelData.h"

namespace mjEngine{

class mjSkybox: public mjObject
{
public:

	mjSkybox(mjResourceManager* resourceManager);


	void SetCameraPos(mjVector3* cameraPos);
	void SetModels(mjModel* boxModel, mjModel* planeModel);
	void LoadTexturesFromPrefix(const char* prefix);
	virtual void PushLevel(mjSkyboxLevelData* data);
	virtual void Update(double t_elapsed) override;

	mjModel* boxModel;
	mjModel* planeModel;

	mjSkyboxLevelData backgroundData;

private:
    mjVector3* cameraPos = NULL;
	std::vector<mjSkyboxLevelData* > levels;
	mjResourceManager* resourceManager;

};

}

#endif
