/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */
#ifndef MJAABB_H
#define MJAABB_H

#include "mjBoundingStructure.h"
#include "../core/mjVector3.h"

namespace mjEngine{

 class mjAABB: public mjBoundingStructure {
	public:
	mjVector3 minCorner;
	mjVector3 maxCorner;
	mjVector3* center;
	mjVector3 halfWidths;
	
	
	mjAABB(mjVector3* center, mjVector3& minCorner, mjVector3& maxCorner, bool isImmovable);
    virtual ~mjAABB();
	void UpdateCorners();
	void UpdateCenter();
	void SetCorners(mjVector3& minCorner, mjVector3& maxCorner);

};

}

#endif
