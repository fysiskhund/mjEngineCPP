#include "mjMathHelper.h"

namespace mjEngine{


float mjMathHelper::Sign(float x)
{
	return (x > 0)? 1:(x== 0)? 0: -1;
}

}
