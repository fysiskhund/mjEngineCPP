#include "mjMathHelper.h"

namespace mjEngine{


float mjMathHelper::Sign(float x)
{
	int res = (x > 0)? 1:(x== 0)? 0: -1;
	LOGI("Sign(%3.3f) -> %d", x, res);
	return res;
}

}
