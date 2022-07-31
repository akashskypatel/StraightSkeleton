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
    Vertex* _nextVertex = nullptr;
    Edge* _oppositeEdge = nullptr;
    Vertex* _previousVertex = nullptr;
public:
    //SingleEdgeChain(Edge oppositeEdge, Vertex nextVertex);
    SingleEdgeChain(spe oppositeEdge, spv nextVertex);
    ~SingleEdgeChain();
    Edge* PreviousEdge();
    Edge* NextEdge();
    Vertex* PreviousVertex();
    Vertex* NextVertex();
    Vertex* CurrentVertex();
    EChainType ChainType();
};

