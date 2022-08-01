#pragma once
#include "Edge.h"
#include "Vertex.h"
#include "EChainType.h"

class IChain
{
private:
	using spe = std::shared_ptr<Edge>;
	using spv = std::shared_ptr<Vertex>;
public:
	spe PreviousEdge;
	spe NextEdge;
	spv PreviousVertex;
	spv NextVertex;
	spv CurrentVertex;
	EChainType ChainType;
};

