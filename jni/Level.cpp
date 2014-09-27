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
            
            
            
		}
        
        if (obj)
        {
            // Read its characteristics
            ReadVector(entity->FirstChildElement("pos"), &obj->pos);
            ReadVector(entity->FirstChildElement("dir"), &obj->dir);
            ReadVector(entity->FirstChildElement("up"), &obj->up);
            ReadVector(entity->FirstChildElement("vel"), &obj->vel);
        }
		entity = entity->NextSiblingElement();
	}

}

void Level::ReadVector(XMLElement* element, mjVector3* v)
{
    if (element)
    {
        element->QueryFloatAttribute("x", &v->x);
        element->QueryFloatAttribute("y", &v->y);
        element->QueryFloatAttribute("z", &v->z);
    }
}