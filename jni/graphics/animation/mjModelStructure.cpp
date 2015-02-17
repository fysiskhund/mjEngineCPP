#include "mjModelStructure.h"

namespace mjEngine{

mjModelStructure::mjModelStructure()
{
    //ctor
}

mjModelStructure::mjModelStructure(const char* fullPath)
{
    XMLDocument doc;

	doc.LoadFile(fileName);
	Load(&doc);
}

mjModelStructure::Load(XMLDocument* doc)
{

}


mjModelStructure::~mjModelStructure()
{
    //dtor
}

}
