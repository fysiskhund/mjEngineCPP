#ifndef LEVEL_H
#define LEVEL_H

#include "extLibs/tinyxml/tinyxml2.h"
#include "mjVector3.h"

using namespace mjEngine;

using namespace tinyxml2;

class Level
{
public:
	void LoadFromFile(const char* fileName);
	void Load(XMLDocument* doc);

private:

};


#endif
