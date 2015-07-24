#ifndef MJMODELSTRUCTURE_H
#define MJMODELSTRUCTURE_H

#include <string>
#include <vector>

#include "mjModelStructureNode.h"
#include "../../extLibs/tinyxml/tinyxml2.h"


using namespace tinyxml2;

namespace mjEngine{




class mjModelStructure
{
    public:
		std::vector<mjModelStructureNode*> nodes;
        mjModelStructure();
        mjModelStructure(const char* fileName);
        void Load(tinyxml2::XMLDocument* doc);
        virtual ~mjModelStructure();
    protected:
    private:
};

}
#endif // MJMODELSTRUCTURE_H
