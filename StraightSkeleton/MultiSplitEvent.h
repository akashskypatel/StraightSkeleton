#ifndef MULTISPLITEVENT_H_
#define MULTISPLITEVENT_H_

#pragma once
#include <vector>
#include "SkeletonEvent.h"
#include "IChain.h"

class MultiSplitEvent :
    public SkeletonEvent
{
private:
    using spv2d = std::shared_ptr<Vector2d>;
    using spvic = std::shared_ptr<std::vector<std::shared_ptr<IChain>>>;
public:
    spvic Chains = nullptr;
    MultiSplitEvent(spv2d point, double distance, spvic chains);
    bool IsObsolete() override;
};

#endif // !MULTISPLITEVENT_H_
