#include "SingleEdgeChain.h"
/*
SingleEdgeChain::SingleEdgeChain(Edge oppositeEdge, Vertex nextVertex)
{
    _oppositeEdge = std::make_shared<Edge>(Edge(oppositeEdge));
    _nextVertex = std::make_shared<Vertex>(Vertex(nextVertex));

    // previous vertex for opposite edge event is valid only before
    // processing of multi split event start. We need to store vertex before
    // processing starts.

    _previousVertex = std::dynamic_pointer_cast<Vertex>(nextVertex.Previous);
    //_previousVertex = dynamic_cast<Vertex*>(nextVertex.Previous.get());
}
*/
SingleEdgeChain::SingleEdgeChain(spe oppositeEdge, spv nextVertex)
{
    _oppositeEdge = oppositeEdge.get();
    _nextVertex = nextVertex.get();
    _previousVertex = dynamic_cast<Vertex*>(nextVertex->Previous.get());
}
SingleEdgeChain::~SingleEdgeChain()
{
    //delete _nextVertex;
    //delete _oppositeEdge;
    //delete _previousVertex;
}

Edge* SingleEdgeChain::PreviousEdge()
{
    return _oppositeEdge;
}

Edge* SingleEdgeChain::NextEdge()
{
    return _oppositeEdge;
}

Vertex* SingleEdgeChain::PreviousVertex()
{
    return _previousVertex;
}

Vertex* SingleEdgeChain::NextVertex()
{
    return _nextVertex;
}

Vertex* SingleEdgeChain::CurrentVertex()
{
    return nullptr;
}

EChainType SingleEdgeChain::ChainType()
{
    return EChainType::SPLIT;
}
