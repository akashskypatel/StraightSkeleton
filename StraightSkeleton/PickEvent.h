#pragma once
#include "SkeletonEvent.h"
#include "EdgeChain.h"
class PickEvent :
    public SkeletonEvent
{
public:
    EdgeChain* Chain;
    PickEvent(Vector2d point, double distance, EdgeChain* chain);
    bool IsObsolete() override;
};

