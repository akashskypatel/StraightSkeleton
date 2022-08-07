#include "MultiEdgeEvent.h"

MultiEdgeEvent::MultiEdgeEvent(spv2d point, double distance, spec chain) : SkeletonEvent(point, distance)
{
    Chain = chain;
}

bool MultiEdgeEvent::IsObsolete()
{
    return false;
}
