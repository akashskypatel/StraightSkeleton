#pragma once
#include <typeinfo>
#include "IChain.h"
#include "SplitEvent.h"
#include "VertexSplitEvent.h"

class SplitChain :
    public IChain
{    
private:
    using spe = std::shared_ptr<Edge>;
    using spv = std::shared_ptr<Vertex>;
    SplitEvent* _splitEvent;
public:
    SplitChain(SplitEvent* event);
    Edge* OppositeEdge();
    Edge* PreviousEdge();
    Edge* NextEdge();
    Vertex* PreviousVertex();
    Vertex* NextVertex();
    Vertex* CurrentVertex();
    EChainType ChainType();
};

