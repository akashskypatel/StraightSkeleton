#include "MultiEdgeEvent.h"

MultiEdgeEvent::MultiEdgeEvent(spv2d point, double distance, spec chain) : SkeletonEvent(point, distance)
{
    Chain = chain.get();
}

bool MultiEdgeEvent::IsObsolete()
{
    return false;
}
