#pragma once
#include <vector>
#include "IChain.h"
#include "EdgeEvent.h"
#include "EChainType.h"

class EdgeChain :
    public IChain
{
private:
    using spe = std::shared_ptr<Edge>;
    using spv = std::shared_ptr<Vertex>;
    bool _closed;
public:
    std::vector<EdgeEvent>* EdgeList = nullptr;
    EdgeChain(std::vector<EdgeEvent>* edgeList);
    spe PreviousEdge();
    spe NextEdge();
    spv PreviousVertex();
    spv CurrentVertex();
    EChainType ChainType();
};

