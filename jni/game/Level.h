#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "../extLibs/tinyxml/tinyxml2.h"
#include "../core/mjObject.h"
//#include "EntityCreator.h"
#include "TerrainCreator.h"

//#include "..Box.h"
#include "../core/mjVector3.h"
#include <string.h>

#include "../extLibs/util/mjXMLHelper.h"
#include "../util/mjResourceManager.h"


using namespace tinyxml2;

class Level
{
public:

	std::vector<mjObject*> entities;
	std::vector<mjObject*> terrain;

    Level(mjResourceManager* resourceManager);
    virtual ~Level();
	void LoadFromFile(const char* fileName);
    void Load(tinyxml2::XMLDocument* doc);
    mjObject* GetEntityByID(const char* ID);
    void Unload();

    tinyxml2::XMLDocument doc;

    mjVector3 levelCenter;
    mjAABB* bounds;

    float hardLimitExtra = 0.5; // extra space given so things can wander a bit outside the world
    mjAABB* hardLimits; // now with hardLimitExtra% more space than bounds

private:
    mjResourceManager* resourceManager;
    //EntityCreator entityCreator;
    TerrainCreator terrainCreator;

};


#endif
