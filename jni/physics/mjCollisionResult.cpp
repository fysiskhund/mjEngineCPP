#include "mjCollisionResult.h"

namespace mjEngine{

mjCollisionResult::mjCollisionResult()
{
	relocationEffectObj0 = NULL;
	changeVelEffectObj0 = NULL;
	relocationEffectObj1 = NULL;
	changeVelEffectObj1 = NULL;
}

mjCollisionResult::~mjCollisionResult()
{
	if (relocationEffectObj0 != NULL)
	{
		delete relocationEffectObj0;
	}
	if (changeVelEffectObj0 != NULL)
	{
		delete changeVelEffectObj0;
	}
	if (relocationEffectObj1 != NULL)
	{
		delete relocationEffectObj1;
	}
	if (changeVelEffectObj1 != NULL)
	{
		delete changeVelEffectObj1;
	}
}
}
