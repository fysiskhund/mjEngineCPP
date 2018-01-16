#include "mjSkyboxLevelData.h"


namespace mjEngine
{



mjSkyboxLevelData::mjSkyboxLevelData()
{
	// Nothing.
}
mjSkyboxLevelData::mjSkyboxLevelData(GLuint texture, float angleH, float angleV, float deltaH, float deltaV )
{
	this->texture = texture;

	this->angleH = angleH;
	this->angleV = angleV;

	this->deltaH = deltaH;
	this->deltaV = deltaV;
	//LOGI("skyboxLevelData tex: %d", texture);
}

void mjSkyboxLevelData::Update(double t_elapsed)
{
	angleH += deltaH*t_elapsed;
    if (angleH > MJ_TWICE_PI)
	{
        angleH -= MJ_TWICE_PI;
	} else if (angleH < 0)
	{
        angleH += MJ_TWICE_PI;
	}

	angleV += deltaV*t_elapsed;
    if (angleV > MJ_TWICE_PI)
	{
        angleV -= MJ_TWICE_PI;
	} else if (angleV < 0)
	{
        angleV += MJ_TWICE_PI;
	}

}

}
