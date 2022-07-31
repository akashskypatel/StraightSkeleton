#pragma once
#include <vector>
#include "SkeletonEvent.h"
#include "IChain.h"

class MultiSplitEvent :
    public SkeletonEvent
{
private:
    using spv2d = std::shared_ptr<Vector2d>;
public:
    std::vector<IChain>* Chains;
    MultiSplitEvent(spv2d point, double distance, std::vector<IChain>* chains);
    bool IsObsolete() override;
};

