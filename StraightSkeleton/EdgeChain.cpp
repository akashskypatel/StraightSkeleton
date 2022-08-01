#include "EdgeChain.h"

EdgeChain::EdgeChain(std::vector<EdgeEvent>* edgeList)
{
    EdgeList = edgeList;
    _closed = PreviousVertex() == NextVertex;
}

std::shared_ptr<Edge> EdgeChain::PreviousEdge()
{
    return EdgeList->at(0).PreviousVertex->PreviousEdge;
}

std::shared_ptr<Edge> EdgeChain::NextEdge()
{
    return EdgeList->at(EdgeList->size() - 1).NextVertex->NextEdge;
}

Vertex* EdgeChain::PreviousVertex()
{
    return EdgeList->at(0).PreviousVertex;
}

Vertex* EdgeChain::CurrentVertex()
{
    return nullptr;
}

EChainType EdgeChain::ChainType()
{
    return (_closed ? EChainType::CLOSED_EDGE : EChainType::EDGE);
}
