#ifndef _MULTISPLITEVENT_H_
#define _MULTISPLITEVENT_H_

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

#endif // !_MULTISPLITEVENT_H_
