#ifndef MJMODELSTRUCTURE_H
#define MJMODELSTRUCTURE_H

#include <string>
#include <vector>

#include "../../extLibs/tinyxml/tinyxml2.h"
#include "mjModelStructureNode.h"


using namespace tinyxml2;

namespace mjEngine{




class mjModelStructure
{
    public:
		std::vector<mjModelStructureNode*> nodes;
        mjModelStructure();
        mjModelStructure(const char* fileName);
        void Load(XMLDocument* doc);
        virtual ~mjModelStructure();
    protected:
    private:
};

}
#endif // MJMODELSTRUCTURE_H
