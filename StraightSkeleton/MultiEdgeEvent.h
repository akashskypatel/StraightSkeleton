#pragma once
#include "SkeletonEvent.h"
#include "EdgeChain.h"

class MultiEdgeEvent :
    public SkeletonEvent
{
public:
    EdgeChain* Chain;
    MultiEdgeEvent(Vector2d point, double distance, EdgeChain* chain);
    bool IsObsolete() override;
};

