/*
 * Copyright (C) 2014 Alejandro Valenzuela Roca
 */
#ifndef MJAABB_H
#define MJAABB_H

namespace mjEngine{

 class mjAABB: public mjBoundingStructure {
	public:
	mjVector3 minCorner;
	mjVector3 maxCorner;
	mjVector3 center;
	mjVector3 halfWidths;
	
	
	mjAABB(mjVector3 minCorner, mjVector3 maxCorner, bool isImmovable);
	void UpdateCorners();

};

}

#endif
