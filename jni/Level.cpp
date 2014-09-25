#include "Level.h"


void Level::LoadFromFile(const char* fileName)
{
	XMLDocument doc;

	doc.LoadFile(fileName);
	Load(&doc);
}

void Level::Load(XMLDocument* doc)
{

}
