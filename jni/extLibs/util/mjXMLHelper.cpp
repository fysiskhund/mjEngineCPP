#include "mjXMLHelper.h"

namespace mjEngine
{

void mjXMLHelper::ReadVector(XMLElement* element, mjVector3* v)
{
    if (element)
    {
        element->QueryFloatAttribute("x", &v->x);
        element->QueryFloatAttribute("y", &v->y);
        element->QueryFloatAttribute("z", &v->z);
    }

}

}
