#include "mjModelStructure.h"

namespace mjEngine{

mjModelStructure::mjModelStructure()
{
    //ctor
}

mjModelStructure::mjModelStructure(const char* fileName)
{
    XMLDocument doc;

	doc.LoadFile(fileName);
	Load(&doc);
}

void mjModelStructure::Load(XMLDocument* doc)
{

}


mjModelStructure::~mjModelStructure()
{
    //dtor
}

}
