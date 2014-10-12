#ifndef MJXMLHELPER_H
#define MJXMLHELPER_H

#include "../../core/mjVector3.h"
#include "../tinyxml/tinyxml2.h"

namespace mjEngine{

using namespace tinyxml2;

class mjXMLHelper
{
    public:

        static void ReadVector(XMLElement* element, mjVector3* v);
    protected:
    private:
};

}
#endif // MJXMLHELPER_H
