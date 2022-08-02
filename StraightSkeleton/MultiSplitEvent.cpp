#include "MultiSplitEvent.h"

MultiSplitEvent::MultiSplitEvent(spv2d point, double distance, spvic chains)
    : SkeletonEvent(point, distance)
{
    Chains = chains;
}

bool MultiSplitEvent::IsObsolete()
{
    return false;
}
