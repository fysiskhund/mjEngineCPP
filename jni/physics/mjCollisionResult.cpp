#include "mjCollisionResult.h"

namespace mjEngine{

mjCollisionResult::mjCollisionResult()
{
	effectObj0 = NULL;
	effectObj1 = NULL;
}

mjCollisionResult::~mjCollisionResult()
{
	if (effectObj0 != NULL)
	{
		delete effectObj0;
	}
	if (effectObj1 != NULL)
	{
		delete effectObj1;
	}
}
}
