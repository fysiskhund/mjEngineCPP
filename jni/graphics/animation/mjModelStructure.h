#ifndef MJMODELSTRUCTURE_H
#define MJMODELSTRUCTURE_H

#include "../../extLibs/tinyxml/tinyxml2.h"

namespace mjEngine{
using namespace tinyxml2;

class mjModelStructure
{
    public:
        mjModelStructure();
        mjModelStructure(const char* fileName);
        void Load(XMLDocument* doc);
        virtual ~mjModelStructure();
    protected:
    private:
};

}
#endif // MJMODELSTRUCTURE_H
