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
    using spvee = std::shared_ptr<std::vector<std::shared_ptr<EdgeEvent>>>;
    bool _closed;
public:
    spvee EdgeList = nullptr;
    EdgeChain(spvee edgeList);
    ~EdgeChain() override;
    spe PreviousEdge();
    spe NextEdge();
    spv PreviousVertex();
    spv CurrentVertex();
    EChainType ChainType();
};

