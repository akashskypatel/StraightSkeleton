#include "MultiSplitEvent.h"

MultiSplitEvent::MultiSplitEvent(spv2d point, double distance, std::vector<IChain>* chains)
    : SkeletonEvent(point, distance)
{
    Chains = chains;
}

bool MultiSplitEvent::IsObsolete()
{
    return false;
}
