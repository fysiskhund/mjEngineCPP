#include "mjSkyboxLevelData.h"


namespace mjEngine
{



#define TWICE_PI 6.283184

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
	LOGI("skyboxLevelData tex: %d", texture);
}

void mjSkyboxLevelData::Update(float t_elapsed)
{
	angleH += deltaH*t_elapsed;
	if (angleH > TWICE_PI)
	{
		angleH -= TWICE_PI;
	} else if (angleH < 0)
	{
		angleH += TWICE_PI;
	}

	angleV += deltaV*t_elapsed;
	if (angleV > TWICE_PI)
	{
		angleV -= TWICE_PI;
	} else if (angleV < 0)
	{
		angleV += TWICE_PI;
	}

}

}
