#include "mjAABB.h"

namespace mjEngine{

mjAABB::mjAABB(mjVector3& minCorner, mjVector3& maxCorner, bool isImmovable)
{
		this->minCorner = minCorner;
		this->maxCorner = maxCorner;
		
		halfWidths = new mjVector3(maxCorner);
		halfWidths.Sum(-1, minCorner);
		halfWidths.MulScalar(0.5f);
		
		center = new mjVector3(minCorner);
		center.Sum(halfWidths);
		this->isImmovable = isImmovable;
		this->type = MJ_AABB;
}

void mjAABB::UpdateCorners()
{
	this->minCorner.Copy(center);
	this->minCorner.Sum(-1, halfWidths);
	this->maxCorner.Copy(center);
	this->maxCorner.Sum(halfWidths);
}
}
