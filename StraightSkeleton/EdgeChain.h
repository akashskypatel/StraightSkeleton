#pragma once
#include <vector>
#include "IChain.h"
#include "EdgeEvent.h"
#include "EChainType.h"

class EdgeChain :
    public IChain
{
private:
    bool _closed;
public:
    std::vector<EdgeEvent>* EdgeList = nullptr;
    EdgeChain(std::vector<EdgeEvent>* edgeList);
    Edge* PreviousEdge();
    Edge* NextEdge();
    Vertex* PreviousVertex();
    Vertex* CurrentVertex();
    EChainType ChainType();
};

