#include "SplitChain.h"

SplitChain::SplitChain(SplitEvent* event)
{
    _splitEvent = event;
}

Edge* SplitChain::OppositeEdge()
{
    if (typeid(*_splitEvent) == typeid(VertexSplitEvent))
        return _splitEvent->OppositeEdge;
    return nullptr;
}

Edge* SplitChain::PreviousEdge()
{
    return _splitEvent->Parent->PreviousEdge;
}

Edge* SplitChain::NextEdge()
{
    return _splitEvent->Parent->NextEdge;
}

Vertex* SplitChain::PreviousVertex()
{
    return dynamic_cast<Vertex*>(_splitEvent->Parent->Previous.get());
}

Vertex* SplitChain::NextVertex()
{
    return dynamic_cast<Vertex*>(_splitEvent->Parent->Next.get());
}

Vertex* SplitChain::CurrentVertex()
{
    return _splitEvent->Parent;
}

EChainType SplitChain::ChainType()
{
    return EChainType::SPLIT;
}
