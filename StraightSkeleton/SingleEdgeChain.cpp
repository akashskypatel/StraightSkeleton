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
    _oppositeEdge = oppositeEdge;
    _nextVertex = nextVertex;
    _previousVertex = dynamic_pointer_cast<Vertex>(nextVertex->Previous);
}
SingleEdgeChain::~SingleEdgeChain()
{
    //delete _nextVertex;
    //delete _oppositeEdge;
    //delete _previousVertex;
}

std::shared_ptr<Edge> SingleEdgeChain::PreviousEdge()
{
    return _oppositeEdge;
}

std::shared_ptr<Edge> SingleEdgeChain::NextEdge()
{
    return _oppositeEdge;
}

std::shared_ptr<Vertex> SingleEdgeChain::PreviousVertex()
{
    return _previousVertex;
}

std::shared_ptr<Vertex> SingleEdgeChain::NextVertex()
{
    return _nextVertex;
}

std::shared_ptr<Vertex> SingleEdgeChain::CurrentVertex()
{
    return nullptr;
}

EChainType SingleEdgeChain::ChainType()
{
    return EChainType::SPLIT;
}
