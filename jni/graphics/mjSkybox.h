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
	virtual void TieShaders(std::vector<mjShader*>& shaderList) override;
	virtual void PushLevel(mjSkyboxLevelData* data);
	virtual void Update(float t_elapsed) override;
	virtual void Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix) override;

	mjModel* boxModel;
	mjModel* planeModel;

	mjSkyboxLevelData backgroundData;

private:
	mjVector3* cameraPos;
	std::vector<mjSkyboxLevelData* > levels;
	mjResourceManager* resourceManager;

};

}

#endif
