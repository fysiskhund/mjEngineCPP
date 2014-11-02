#ifndef MJSKYBOXLEVELDATA_H
#define MJSKYBOXLEVELDATA_H

#include "../extLibs/util/mjMultiPlatform.h"

#include "../extLibs/logger/mjLog.h"

namespace mjEngine{

class mjSkyboxLevelData
{
public:

	mjSkyboxLevelData();
	mjSkyboxLevelData(GLuint texture, float angleH, float angleV, float deltaH, float deltaV );

	void Update(float t_elapsed);
	GLuint texture = 0;
	float angleH = 0;
	float angleV = 0;

	float deltaH = 0;
	float deltaV = 0;

};


}

#endif
