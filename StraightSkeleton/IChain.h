#pragma once
#include "Edge.h"
#include "Vertex.h"
#include "EChainType.h"

class IChain
{
public:
	Edge* PreviousEdge;
	Edge* NextEdge;
	Vertex* PreviousVertex;
	Vertex* NextVertex;
	Vertex* CurrentVertex;
	EChainType ChainType;
};

