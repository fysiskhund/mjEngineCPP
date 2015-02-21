#ifndef MJMODELSTRUCTURENODE_H
#define MJMODELSTRUCTURENODE_H

namespace mjEngine{

enum modelStructureNodeType {MJ_NODE_PUSH, MJ_NODE_POP, MJ_NODE_NOOP, MJ_NODE_RESET };

class mjModelStructureNode
{
    public:
		modelStructureNodeType operation;
		std::string meshName;
		int meshIndex;
        mjModelStructureNode();
        virtual ~mjModelStructureNode();
    protected:
    private:
};

}

#endif // MJMODELSTRUCTURENODE_H
