#include "Level.h"


void Level::LoadFromFile(const char* fileName)
{
	XMLDocument doc;

	doc.LoadFile(fileName);
	Load(&doc);
}

void Level::Load(XMLDocument* doc)
{
	XMLHandle docHandle(doc);


	XMLElement* entity = docHandle.FirstChildElement("level").FirstChildElement("entities").FirstChild().ToElement();

	while (entity)
	{
		mjObject* obj = NULL;
		if (strncmp(entity->Name(), "player", 200) == 0)
		{
			obj = new Character(MJ_AABB);
			if (entity->FirstChildElement("pos"))
			{

			}
		}
		entity = entity->NextSiblingElement();
	}

}
