#include "mjAABB.h"

namespace mjEngine{

mjAABB::mjAABB(mjVector3* center, mjVector3& minCorner, mjVector3& maxCorner, bool isImmovable)
{
		this->minCorner.CopyFrom(minCorner);
		this->maxCorner.CopyFrom(maxCorner);
		
		halfWidths.CopyFrom(maxCorner);
		halfWidths.Subtract(minCorner);
		halfWidths.MulScalar(0.5f);
		
		center->CopyFrom(minCorner);
		center->Add(halfWidths);
		this->isImmovable = isImmovable;
		this->type = MJ_AABB;
}

void mjAABB::UpdateCorners()
{
	this->minCorner.CopyFrom(*center);
	this->minCorner.Subtract(halfWidths);
	this->maxCorner.CopyFrom(*center);
	this->maxCorner.Add(halfWidths);
}
}
