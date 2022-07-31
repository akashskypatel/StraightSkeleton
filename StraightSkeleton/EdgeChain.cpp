#include "EdgeChain.h"

EdgeChain::EdgeChain(std::vector<EdgeEvent>* edgeList)
{
    EdgeList = edgeList;
    _closed = PreviousVertex() == NextVertex;
}

Edge* EdgeChain::PreviousEdge()
{
    return EdgeList->at(0).PreviousVertex->PreviousEdge.get();
}

Edge* EdgeChain::NextEdge()
{
    return EdgeList->at(EdgeList->size() - 1).NextVertex->NextEdge.get();
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
