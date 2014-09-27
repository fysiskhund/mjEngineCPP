#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "extLibs/tinyxml/tinyxml2.h"
#include "core/mjObject.h"
#include "EntityCreator.h"

//#include "Box.h"
#include "core/mjVector3.h"
#include <string.h>

using namespace mjEngine;

using namespace tinyxml2;

class Level
{
public:

	std::vector<mjObject*> entities;

	void LoadFromFile(const char* fileName);
	void Load(XMLDocument* doc);

private:
    void ReadVector(XMLElement* element, mjVector3* v);
    EntityCreator entityCreator;

};


#endif
