#include "SplitChain.h"

SplitChain::SplitChain(SplitEvent* event)
{
    _splitEvent = event;
}

Edge* SplitChain::OppositeEdge()
{
    if (typeid(*_splitEvent) == typeid(VertexSplitEvent))
        return _splitEvent->OppositeEdge.get();
    return nullptr;
}

Edge* SplitChain::PreviousEdge()
{
    return _splitEvent->Parent->PreviousEdge.get();
}

Edge* SplitChain::NextEdge()
{
    return _splitEvent->Parent->NextEdge.get();
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
    return _splitEvent->Parent.get();
}

EChainType SplitChain::ChainType()
{
    return EChainType::SPLIT;
}
