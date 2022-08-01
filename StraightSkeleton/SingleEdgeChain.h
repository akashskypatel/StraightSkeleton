#pragma once
#include "IChain.h"
#include "CircularList.h"
#include "EChainType.h"

class SingleEdgeChain :
    public IChain
{
private:
    using spv = std::shared_ptr<Vertex>;
    using spe = std::shared_ptr<Edge>;
    spv _nextVertex = nullptr;
    spe _oppositeEdge = nullptr;
    spv _previousVertex = nullptr;
public:
    //SingleEdgeChain(Edge oppositeEdge, Vertex nextVertex);
    SingleEdgeChain(spe oppositeEdge, spv nextVertex);
    ~SingleEdgeChain();
    spe PreviousEdge();
    spe NextEdge();
    spv PreviousVertex();
    spv NextVertex();
    spv CurrentVertex();
    EChainType ChainType();
};

