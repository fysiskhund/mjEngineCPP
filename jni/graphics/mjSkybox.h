#ifndef MJ_SKYBOX_H
#define MJ_SKYBOX_H

#include <vector>
#include "../core/mjObject.h"

namespace mjEngine{

class mjSkybox: public mjObject
{
public:

	mjSkybox();


	void SetCameraPos(mjVector3* cameraPos);
	void SetModels(mjModel* boxModel, mjModel* planeModel);
	virtual void PushLevel(GLuint texture);
	virtual void Update(float t_elapsed) override;
	virtual void Draw(std::vector<mjShader*>& shaderList, float* lookAtMatrix, float* projectionMatrix) override;

private:
	mjVector3* cameraPos;
	std::vector<GLuint> levels;

	mjModel* boxModel;
	mjModel* planeModel;

};

}

#endif
