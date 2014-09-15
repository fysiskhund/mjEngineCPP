#ifndef MJ_SKYBOX_H
#define MJ_SKYBOX_H

#include "../core/mjObject.h"

namespace mjEngine{

class mjSkybox: public mjObject
{
public:

	mjSkybox();
	void SetCameraPos(mjVector3* cameraPos);
	virtual void Update(float t_elapsed) override;
	virtual void Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix) override;
private:
	mjVector3* cameraPos;
};

}

#endif
