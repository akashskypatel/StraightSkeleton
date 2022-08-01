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
    std::shared_ptr<Edge> PreviousEdge();
    std::shared_ptr<Edge> NextEdge();
    Vertex* PreviousVertex();
    Vertex* CurrentVertex();
    EChainType ChainType();
};

