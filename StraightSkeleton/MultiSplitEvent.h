#pragma once
#include <vector>
#include "SkeletonEvent.h"
#include "IChain.h"

class MultiSplitEvent :
    public SkeletonEvent
{
public:
    std::vector<IChain>* Chains;
    MultiSplitEvent(Vector2d point, double distance, std::vector<IChain>* chains);
    bool IsObsolete() override;
};

