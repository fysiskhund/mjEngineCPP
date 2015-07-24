#include "mjModelStructure.h"

namespace mjEngine{

mjModelStructure::mjModelStructure()
{
    //ctor
}

mjModelStructure::mjModelStructure(const char* fileName)
{
    tinyxml2::XMLDocument doc;

	doc.LoadFile(fileName);
	Load(&doc);
}

void mjModelStructure::Load(tinyxml2::XMLDocument* doc)
{

}


mjModelStructure::~mjModelStructure()
{
    //dtor
}

}
