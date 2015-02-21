#ifndef MJMODELSTRUCTURE_H
#define MJMODELSTRUCTURE_H

#include "../../extLibs/tinyxml/tinyxml2.h"
#include <vector>

using namespace tinyxml2;

namespace mjEngine{




class mjModelStructure
{
    public:
		std::vector<modelStructureNodeType> nodes;
        mjModelStructure();
        mjModelStructure(const char* fileName);
        void Load(XMLDocument* doc);
        virtual ~mjModelStructure();
    protected:
    private:
};

}
#endif // MJMODELSTRUCTURE_H
